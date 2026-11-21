
#include "hurtip/interpreter.hpp"

#include "hurtip/lexer.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace hurtip
{

    namespace
    {

        struct BreakSignal
        {
            int line;
        };

        struct ContinueSignal
        {
            int line;
        };

        struct ReturnSignal
        {
            RuntimeValue value;
        };

    }

    // Interpreter entry points

    void Interpreter::interpret(
        const std::vector<std::unique_ptr<ASTNode>> &statements)
    {
        currentFilePath.clear();

        executeStatements(statements);
    }

    void Interpreter::interpret(
        const std::vector<std::unique_ptr<ASTNode>> &statements,
        const std::filesystem::path &sourcePath)
    {
        currentFilePath =
            std::filesystem::absolute(sourcePath).lexically_normal();

        std::error_code error;

        std::filesystem::path canonicalPath =
            std::filesystem::weakly_canonical(
                currentFilePath,
                error);

        if (!error)
        {
            currentFilePath = canonicalPath;
        }

        executeStatements(statements);
    }

    // Statement execution

    void Interpreter::executeStatements(
        const std::vector<std::unique_ptr<ASTNode>> &statements)
    {
        for (const auto &statement : statements)
        {
            try
            {
                execute(*statement);
            }
            catch (const BreakSignal &signal)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(signal.line) +
                    ": 'break' can only be used inside a loop");
            }
            catch (const ContinueSignal &signal)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(signal.line) +
                    ": 'continue' can only be used inside a loop");
            }
        }
    }

    void Interpreter::execute(const ASTNode &statement)
    {
        // Variable declaration

        if (const auto *create =
                dynamic_cast<const CreateStatement *>(&statement))
        {
            RuntimeValue value = evaluate(*create->value);

            variables[create->name] = value;

            return;
        }

        // Variable assignment

        if (const auto *assignment =
                dynamic_cast<const AssignmentStatement *>(&statement))
        {
            auto variable = variables.find(assignment->name);

            if (variable == variables.end())
            {
                throw std::runtime_error(
                    "Line " + std::to_string(assignment->line) +
                    ": Undefined variable: " + assignment->name);
            }

            RuntimeValue value = evaluate(*assignment->value);

            variable->second = value;

            return;
        }

        // Load statement

        if (const auto *load =
                dynamic_cast<const LoadStatement *>(&statement))
        {
            executeLoad(*load);

            return;
        }

        // Function declaration

        if (const auto *function =
                dynamic_cast<const FunctionDeclaration *>(&statement))
        {
            if (functions.find(function->name) != functions.end())
            {
                throw std::runtime_error(
                    "Line " + std::to_string(function->line) +
                    ": Function already declared: " + function->name);
            }

            functions.emplace(function->name, function);

            return;
        }

        // Return statement

        if (const auto *returnStatement =
                dynamic_cast<const ReturnStatement *>(&statement))
        {
            RuntimeValue value = std::string("");

            if (returnStatement->value)
            {
                value = evaluate(*returnStatement->value);
            }

            throw ReturnSignal{value};
        }

        // If statement

        if (const auto *ifStatement =
                dynamic_cast<const IfStatement *>(&statement))
        {
            RuntimeValue condition =
                evaluate(*ifStatement->condition);

            const bool *boolean = std::get_if<bool>(&condition);

            if (!boolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(ifStatement->line) +
                    ": If condition must be a boolean");
            }

            if (*boolean)
            {
                execute(*ifStatement->thenBranch);
            }
            else if (ifStatement->elseBranch)
            {
                execute(*ifStatement->elseBranch);
            }

            return;
        }

        // Break statement

        if (const auto *breakStatement =
                dynamic_cast<const BreakStatement *>(&statement))
        {
            throw BreakSignal{breakStatement->line};
        }

        // Continue statement

        if (const auto *continueStatement =
                dynamic_cast<const ContinueStatement *>(&statement))
        {
            throw ContinueSignal{continueStatement->line};
        }

        // While statement

        if (const auto *whileStatement =
                dynamic_cast<const WhileStatement *>(&statement))
        {
            while (true)
            {
                RuntimeValue condition =
                    evaluate(*whileStatement->condition);

                const bool *boolean =
                    std::get_if<bool>(&condition);

                if (!boolean)
                {
                    throw std::runtime_error(
                        "Line " + std::to_string(whileStatement->line) +
                        ": While condition must be a boolean");
                }

                if (!*boolean)
                {
                    break;
                }

                try
                {
                    execute(*whileStatement->body);
                }
                catch (const ContinueSignal &)
                {
                    continue;
                }
                catch (const BreakSignal &)
                {
                    break;
                }
            }

            return;
        }

        // Block statement

        if (const auto *block =
                dynamic_cast<const BlockStatement *>(&statement))
        {
            for (const auto &blockStatement : block->statements)
            {
                execute(*blockStatement);
            }

            return;
        }

        // Function call as a statement

        if (const auto *call =
                dynamic_cast<const CallExpression *>(&statement))
        {
            executeCall(*call);

            return;
        }

        throw std::runtime_error("Unknown statement");
    }

    // Module loading

    void Interpreter::executeLoad(const LoadStatement &statement)
    {
        std::filesystem::path modulePath(statement.path);

        if (modulePath.extension() != ".hurtip")
        {
            throw std::runtime_error(
                "Line " + std::to_string(statement.line) +
                ": Modules must use the .hurtip extension");
        }

        // Resolve paths relative to the file containing the load statement.

        if (modulePath.is_relative())
        {
            if (!currentFilePath.empty())
            {
                modulePath =
                    currentFilePath.parent_path() / modulePath;
            }
            else
            {
                modulePath =
                    std::filesystem::current_path() / modulePath;
            }
        }

        modulePath = std::filesystem::absolute(modulePath)
                         .lexically_normal();

        std::error_code error;

        std::filesystem::path canonicalPath =
            std::filesystem::weakly_canonical(
                modulePath,
                error);

        if (!error)
        {
            modulePath = canonicalPath;
        }

        const std::string moduleKey = modulePath.string();

        // Avoid loading the same module more than once.

        if (loadedModules.find(moduleKey) != loadedModules.end())
        {
            return;
        }

        // Detect circular dependencies.

        if (loadingModules.find(moduleKey) != loadingModules.end())
        {
            throw std::runtime_error(
                "Line " + std::to_string(statement.line) +
                ": Circular module dependency: " + moduleKey);
        }

        std::ifstream file(modulePath);

        if (!file.is_open())
        {
            throw std::runtime_error(
                "Line " + std::to_string(statement.line) +
                ": Could not open module: " + moduleKey);
        }

        std::stringstream buffer;

        buffer << file.rdbuf();

        if (file.bad())
        {
            throw std::runtime_error(
                "Could not read module: " + moduleKey);
        }

        const std::string source = buffer.str();

        loadingModules.insert(moduleKey);

        const std::filesystem::path previousFilePath =
            currentFilePath;

        try
        {
            Lexer lexer(source);

            std::vector<Token> tokens = lexer.tokenize();

            Parser parser(tokens);

            auto statements = parser.parse();

            // Store the AST at a stable address.
            // This also keeps function declaration pointers valid.

            auto module = std::make_unique<
                std::vector<std::unique_ptr<ASTNode>>>(
                std::move(statements));

            const auto *modulePointer = module.get();

            moduleStatements.push_back(std::move(module));

            // Execute the module in its own file context.

            currentFilePath = modulePath;

            executeStatements(*modulePointer);

            currentFilePath = previousFilePath;

            loadingModules.erase(moduleKey);

            loadedModules.insert(moduleKey);
        }
        catch (...)
        {
            currentFilePath = previousFilePath;

            loadingModules.erase(moduleKey);

            throw;
        }
    }

    // Expression evaluation

    RuntimeValue Interpreter::evaluate(const Expression &expression)
    {
        // Literal values

        if (const auto *literal =
                dynamic_cast<const LiteralExpression *>(&expression))
        {
            switch (literal->type)
            {
            case TokenType::String:
                return literal->value;

            case TokenType::Number:
                return std::stod(literal->value);

            case TokenType::True:
                return true;

            case TokenType::False:
                return false;

            default:
                break;
            }
        }

        // Variable reference

        if (const auto *identifier =
                dynamic_cast<const IdentifierExpression *>(&expression))
        {
            auto variable = variables.find(identifier->name);

            if (variable == variables.end())
            {
                throw std::runtime_error(
                    "Line " + std::to_string(identifier->line) +
                    ": Undefined variable: " + identifier->name);
            }

            return variable->second;
        }

        // Member expression

        if (dynamic_cast<const MemberExpression *>(&expression))
        {
            throw std::runtime_error(
                "Member access is not available yet");
        }

        // Binary expression

        if (const auto *binary =
                dynamic_cast<const BinaryExpression *>(&expression))
        {
            return evaluateBinary(*binary);
        }

        // Unary expression

        if (const auto *unary =
                dynamic_cast<const UnaryExpression *>(&expression))
        {
            return evaluateUnary(*unary);
        }

        // Grouping expression

        if (const auto *grouping =
                dynamic_cast<const GroupingExpression *>(&expression))
        {
            return evaluate(*grouping->expression);
        }

        // Function call inside an expression

        if (const auto *call =
                dynamic_cast<const CallExpression *>(&expression))
        {
            return executeCall(*call);
        }

        throw std::runtime_error("Invalid expression");
    }

    // Binary operations, comparisons and logical operators

    RuntimeValue Interpreter::evaluateBinary(
        const BinaryExpression &expression)
    {
        RuntimeValue left = evaluate(*expression.left);

        // Logical AND with short-circuit evaluation

        if (expression.operation == TokenType::And)
        {
            const bool *leftBoolean = std::get_if<bool>(&left);

            if (!leftBoolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'and' requires boolean operands");
            }

            if (!*leftBoolean)
            {
                return false;
            }

            RuntimeValue right = evaluate(*expression.right);

            const bool *rightBoolean =
                std::get_if<bool>(&right);

            if (!rightBoolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'and' requires boolean operands");
            }

            return *rightBoolean;
        }

        // Logical OR with short-circuit evaluation

        if (expression.operation == TokenType::Or)
        {
            const bool *leftBoolean = std::get_if<bool>(&left);

            if (!leftBoolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'or' requires boolean operands");
            }

            if (*leftBoolean)
            {
                return true;
            }

            RuntimeValue right = evaluate(*expression.right);

            const bool *rightBoolean =
                std::get_if<bool>(&right);

            if (!rightBoolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'or' requires boolean operands");
            }

            return *rightBoolean;
        }

        RuntimeValue right = evaluate(*expression.right);

        const double *leftNumber =
            std::get_if<double>(&left);

        const double *rightNumber =
            std::get_if<double>(&right);

        switch (expression.operation)
        {
        case TokenType::Plus:
        {
            const std::string *leftString =
                std::get_if<std::string>(&left);

            const std::string *rightString =
                std::get_if<std::string>(&right);

            if (leftString && rightString)
            {
                return *leftString + *rightString;
            }

            if (leftNumber && rightNumber)
            {
                return *leftNumber + *rightNumber;
            }

            break;
        }

        case TokenType::Minus:
            if (leftNumber && rightNumber)
            {
                return *leftNumber - *rightNumber;
            }
            break;

        case TokenType::Star:
            if (leftNumber && rightNumber)
            {
                return *leftNumber * *rightNumber;
            }
            break;

        case TokenType::Slash:
            if (leftNumber && rightNumber)
            {
                if (*rightNumber == 0.0)
                {
                    throw std::runtime_error(
                        "Line " + std::to_string(expression.line) +
                        ": Division by zero");
                }

                return *leftNumber / *rightNumber;
            }
            break;

        case TokenType::EqualEqual:
            return left == right;

        case TokenType::BangEqual:
            return left != right;

        case TokenType::Greater:
            if (leftNumber && rightNumber)
            {
                return *leftNumber > *rightNumber;
            }
            break;

        case TokenType::Less:
            if (leftNumber && rightNumber)
            {
                return *leftNumber < *rightNumber;
            }
            break;

        case TokenType::GreaterEqual:
            if (leftNumber && rightNumber)
            {
                return *leftNumber >= *rightNumber;
            }
            break;

        case TokenType::LessEqual:
            if (leftNumber && rightNumber)
            {
                return *leftNumber <= *rightNumber;
            }
            break;

        default:
            break;
        }

        throw std::runtime_error(
            "Line " + std::to_string(expression.line) +
            ": Invalid operands for binary operation");
    }

    // Unary operations

    RuntimeValue Interpreter::evaluateUnary(
        const UnaryExpression &expression)
    {
        RuntimeValue operand = evaluate(*expression.operand);

        // Logical NOT

        if (expression.operation == TokenType::Not)
        {
            const bool *boolean =
                std::get_if<bool>(&operand);

            if (!boolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'not' requires a boolean operand");
            }

            return !*boolean;
        }

        // Numeric unary operators

        const double *number =
            std::get_if<double>(&operand);

        if (!number)
        {
            throw std::runtime_error(
                "Line " + std::to_string(expression.line) +
                ": Unary operator requires a number");
        }

        switch (expression.operation)
        {
        case TokenType::Minus:
            return -*number;

        case TokenType::Plus:
            return *number;

        default:
            throw std::runtime_error(
                "Invalid unary operator");
        }
    }

    // Function execution

    RuntimeValue Interpreter::executeCall(
        const CallExpression &expression)
    {
        // Resolve the function name from the callee.

        const auto *identifier =
            dynamic_cast<const IdentifierExpression *>(
                expression.callee.get());

        if (!identifier)
        {
            throw std::runtime_error(
                "Line " + std::to_string(expression.line) +
                ": Invalid function call");
        }

        const std::string &functionName = identifier->name;

        // Built-in function: view

        if (functionName == "view")
        {
            for (std::size_t i = 0;
                 i < expression.arguments.size();
                 i++)
            {
                RuntimeValue value =
                    evaluate(*expression.arguments[i]);

                std::visit(
                    [](const auto &result)
                    {
                        using T = std::decay_t<decltype(result)>;

                        if constexpr (std::is_same_v<T, bool>)
                        {
                            std::cout
                                << (result ? "true" : "false");
                        }
                        else
                        {
                            std::cout << result;
                        }
                    },
                    value);

                if (i + 1 < expression.arguments.size())
                {
                    std::cout << " ";
                }
            }

            std::cout << '\n';

            return std::string("");
        }

        // Find user-defined function.

        auto functionIterator = functions.find(functionName);

        if (functionIterator == functions.end())
        {
            throw std::runtime_error(
                "Line " + std::to_string(expression.line) +
                ": Unknown function: " + functionName);
        }

        const FunctionDeclaration *function =
            functionIterator->second;

        // Validate argument count.

        if (expression.arguments.size() !=
            function->parameters.size())
        {
            throw std::runtime_error(
                "Line " + std::to_string(expression.line) +
                ": Function '" + functionName +
                "' expects " +
                std::to_string(function->parameters.size()) +
                " argument(s), but received " +
                std::to_string(expression.arguments.size()));
        }

        // Evaluate arguments before creating the function scope.

        std::vector<RuntimeValue> arguments;

        arguments.reserve(expression.arguments.size());

        for (const auto &argument : expression.arguments)
        {
            arguments.push_back(evaluate(*argument));
        }

        // Preserve the current variable environment.

        auto previousVariables = variables;

        RuntimeValue returnValue = std::string("");

        try
        {
            // Bind arguments to function parameters.

            for (std::size_t i = 0;
                 i < function->parameters.size();
                 i++)
            {
                variables[function->parameters[i]] =
                    arguments[i];
            }

            // Execute function body.

            execute(*function->body);
        }
        catch (const ReturnSignal &signal)
        {
            returnValue = signal.value;
        }
        catch (...)
        {
            variables = std::move(previousVariables);

            throw;
        }

        // Restore the previous variable environment.

        variables = std::move(previousVariables);

        return returnValue;
    }

}
