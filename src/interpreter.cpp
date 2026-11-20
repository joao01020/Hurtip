
#include "netuno/interpreter.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace netuno
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

    }

    void Interpreter::interpret(
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

    // Statement execution

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

        // If statement
        if (const auto *ifStatement =
                dynamic_cast<const IfStatement *>(&statement))
        {
            RuntimeValue condition = evaluate(*ifStatement->condition);

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

                const bool *boolean = std::get_if<bool>(&condition);

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

        // Function call
        if (const auto *call =
                dynamic_cast<const CallExpression *>(&statement))
        {
            executeCall(*call);

            return;
        }

        throw std::runtime_error("Unknown statement");
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
            if (call->name == "view")
            {
                executeCall(*call);
                return std::string("");
            }

            throw std::runtime_error(
                "Unknown function: " + call->name);
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

            const bool *rightBoolean = std::get_if<bool>(&right);

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

            const bool *rightBoolean = std::get_if<bool>(&right);

            if (!rightBoolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'or' requires boolean operands");
            }

            return *rightBoolean;
        }

        RuntimeValue right = evaluate(*expression.right);

        const double *leftNumber = std::get_if<double>(&left);
        const double *rightNumber = std::get_if<double>(&right);

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
            const bool *boolean = std::get_if<bool>(&operand);

            if (!boolean)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Operator 'not' requires a boolean operand");
            }

            return !*boolean;
        }

        // Numeric unary operators
        const double *number = std::get_if<double>(&operand);

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

    void Interpreter::executeCall(const CallExpression &expression)
    {
        if (expression.name != "view")
        {
            throw std::runtime_error(
                "Unknown function: " + expression.name);
        }

        if (expression.arguments.size() != 1)
        {
            throw std::runtime_error(
                "Function 'view' expects exactly one argument");
        }

        for (std::size_t i = 0;
             i < expression.arguments.size();
             i++)
        {
            RuntimeValue value = evaluate(*expression.arguments[i]);

            std::visit(
                [](const auto &result)
                {
                    using T = std::decay_t<decltype(result)>;

                    if constexpr (std::is_same_v<T, bool>)
                    {
                        std::cout << (result ? "true" : "false");
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
    }

}
