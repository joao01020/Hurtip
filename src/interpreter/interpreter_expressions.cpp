
#include "hurtip/interpreter/interpreter.hpp"
#include "interpreter_signals.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

namespace hurtip
{
    namespace
    {
        // Runtime value output

        void printRuntimeValue(const RuntimeValue &value)
        {
            std::visit(
                [](const auto &result)
                {
                    using T = std::decay_t<decltype(result)>;

                    if constexpr (std::is_same_v<T, bool>)
                    {
                        std::cout << (result ? "true" : "false");
                    }
                    else if constexpr (
                        std::is_same_v<T, std::shared_ptr<ArrayValue>>)
                    {
                        if (!result)
                        {
                            std::cout << "[]";
                            return;
                        }

                        std::cout << "[";

                        for (std::size_t i = 0;
                             i < result->elements.size();
                             ++i)
                        {
                            if (i > 0)
                            {
                                std::cout << ", ";
                            }

                            printRuntimeValue(result->elements[i]);
                        }

                        std::cout << "]";
                    }
                    else
                    {
                        std::cout << result;
                    }
                },
                value);
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
            RuntimeValue value;

            if (!currentEnvironment->get(identifier->name, value))
            {
                throw std::runtime_error(
                    "Line " + std::to_string(identifier->line) +
                    ": Undefined variable: " + identifier->name);
            }

            return value;
        }

        // Array creation

        if (const auto *array =
                dynamic_cast<const ArrayExpression *>(&expression))
        {
            auto result = std::make_shared<ArrayValue>();

            result->elements.reserve(array->elements.size());

            for (const auto &element : array->elements)
            {
                result->elements.push_back(evaluate(*element));
            }

            return result;
        }

        // Array indexing

        if (const auto *index =
                dynamic_cast<const IndexExpression *>(&expression))
        {
            RuntimeValue object = evaluate(*index->object);
            RuntimeValue indexValue = evaluate(*index->index);

            const auto *array =
                std::get_if<std::shared_ptr<ArrayValue>>(&object);

            if (!array || !*array)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(index->line) +
                    ": Index access requires an array");
            }

            const auto *number =
                std::get_if<double>(&indexValue);

            if (!number)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(index->line) +
                    ": Array index must be a number");
            }

            if (!std::isfinite(*number) ||
                *number < 0.0 ||
                std::floor(*number) != *number)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(index->line) +
                    ": Array index must be a non-negative integer");
            }

            if (*number >= static_cast<double>(
                               (*array)->elements.size()))
            {
                throw std::runtime_error(
                    "Line " + std::to_string(index->line) +
                    ": Array index out of range");
            }

            return (*array)->elements[static_cast<std::size_t>(*number)];
        }

        // Member expression

        if (const auto *member =
                dynamic_cast<const MemberExpression *>(&expression))
        {
            RuntimeValue object = evaluate(*member->object);

            const auto *array =
                std::get_if<std::shared_ptr<ArrayValue>>(&object);

            if (array && *array)
            {
                if (member->member == "length")
                {
                    return static_cast<double>(
                        (*array)->elements.size());
                }

                throw std::runtime_error(
                    "Line " + std::to_string(member->line) +
                    ": Unknown array property: " + member->member);
            }

            throw std::runtime_error(
                "Line " + std::to_string(member->line) +
                ": Property access requires an array");
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
        std::string functionName;
        std::string targetNamespace;

        const FunctionDeclaration *function = nullptr;
        NativeFunction nativeFunction;

        // Unqualified function call

        if (const auto *identifier =
                dynamic_cast<const IdentifierExpression *>(
                    expression.callee.get()))
        {
            functionName = identifier->name;

            // Built-in function: view

            if (functionName == "view")
            {
                for (std::size_t i = 0;
                     i < expression.arguments.size();
                     i++)
                {
                    RuntimeValue value =
                        evaluate(*expression.arguments[i]);

                    printRuntimeValue(value);

                    if (i + 1 < expression.arguments.size())
                    {
                        std::cout << " ";
                    }
                }

                std::cout << '\n';

                return std::string("");
            }

            // Search in the current namespace first.

            if (!currentNamespace.empty())
            {
                auto namespaceIterator =
                    namespaces.find(currentNamespace);

                if (namespaceIterator != namespaces.end())
                {
                    auto functionIterator =
                        namespaceIterator->second.find(functionName);

                    if (functionIterator !=
                        namespaceIterator->second.end())
                    {
                        function = functionIterator->second;
                        targetNamespace = currentNamespace;
                    }
                }
            }

            // Fall back to global functions.

            if (!function)
            {
                auto functionIterator =
                    functions.find(functionName);

                if (functionIterator != functions.end())
                {
                    function = functionIterator->second;
                    targetNamespace.clear();
                }
            }
        }

        // Qualified function call: namespace.function()

        else if (const auto *member =
                     dynamic_cast<const MemberExpression *>(
                         expression.callee.get()))
        {
            const auto *object =
                dynamic_cast<const IdentifierExpression *>(
                    member->object.get());

            if (!object)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Invalid namespace expression");
            }

            targetNamespace = object->name;
            functionName = member->member;

            // Check imported native libraries first.

            auto imported =
                importedLibraries.find(targetNamespace);

            if (imported != importedLibraries.end())
            {
                auto library =
                    nativeLibraries.find(imported->second);

                if (library == nativeLibraries.end())
                {
                    throw std::runtime_error(
                        "Native library not registered: " +
                        imported->second);
                }

                auto native =
                    library->second.find(functionName);

                if (native == library->second.end())
                {
                    throw std::runtime_error(
                        "Line " + std::to_string(expression.line) +
                        ": Unknown function '" + functionName +
                        "' in library '" + imported->second + "'");
                }

                nativeFunction = native->second;
            }
            else
            {
                // Existing Hurtip module namespace.

                auto namespaceIterator =
                    namespaces.find(targetNamespace);

                if (namespaceIterator == namespaces.end())
                {
                    throw std::runtime_error(
                        "Line " + std::to_string(expression.line) +
                        ": Unknown namespace: " + targetNamespace);
                }

                auto functionIterator =
                    namespaceIterator->second.find(functionName);

                if (functionIterator ==
                    namespaceIterator->second.end())
                {
                    throw std::runtime_error(
                        "Line " + std::to_string(expression.line) +
                        ": Unknown function '" + functionName +
                        "' in namespace '" + targetNamespace + "'");
                }

                function = functionIterator->second;
            }
        }
        else
        {
            throw std::runtime_error(
                "Line " + std::to_string(expression.line) +
                ": Invalid function call");
        }

        // Execute native function.

        if (nativeFunction)
        {
            std::vector<RuntimeValue> arguments;

            arguments.reserve(expression.arguments.size());

            for (const auto &argument : expression.arguments)
            {
                arguments.push_back(evaluate(*argument));
            }

            try
            {
                return nativeFunction(arguments);
            }
            catch (const std::exception &error)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(expression.line) +
                    ": Native function '" + functionName +
                    "' failed: " + error.what());
            }
        }

        if (!function)
        {
            throw std::runtime_error(
                "Line " + std::to_string(expression.line) +
                ": Unknown function: " + functionName);
        }

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

        // Evaluate arguments before changing the function context.

        std::vector<RuntimeValue> arguments;

        arguments.reserve(expression.arguments.size());

        for (const auto &argument : expression.arguments)
        {
            arguments.push_back(evaluate(*argument));
        }

        // Preserve the current execution context.

        auto previousEnvironment = currentEnvironment;

        const std::string previousNamespace =
            currentNamespace;

        RuntimeValue returnValue = std::string("");

        try
        {
            // Create an isolated environment for this function call.

            currentEnvironment =
                std::make_shared<Environment>(globalEnvironment);

            currentNamespace = targetNamespace;

            // Bind arguments to function parameters.

            for (std::size_t i = 0;
                 i < function->parameters.size();
                 i++)
            {
                currentEnvironment->define(
                    function->parameters[i],
                    arguments[i]);
            }

            // Execute function body.

            execute(*function->body);
        }
        catch (const detail::ReturnSignal &signal)
        {
            returnValue = signal.value;
        }
        catch (...)
        {
            currentEnvironment = previousEnvironment;
            currentNamespace = previousNamespace;

            throw;
        }

        // Restore the previous execution context.

        currentEnvironment = previousEnvironment;
        currentNamespace = previousNamespace;

        return returnValue;
    }
}
