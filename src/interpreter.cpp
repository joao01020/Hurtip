
#include "netuno/interpreter.hpp"

#include <iostream>
#include <stdexcept>

namespace netuno
{

    void Interpreter::interpret(
        const std::vector<std::unique_ptr<ASTNode>> &statements)
    {
        for (const auto &statement : statements)
        {
            execute(*statement);
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

        // Function call
        if (const auto *call =
                dynamic_cast<const CallExpression *>(&statement))
        {

            executeCall(*call);

            return;
        }

        throw std::runtime_error("Unknown statement");
    }

    RuntimeValue Interpreter::evaluate(const Expression &expression)
    {

        // Literal value
        if (const auto *literal =
                dynamic_cast<const LiteralExpression *>(&expression))
        {

            if (literal->type == TokenType::String)
            {
                return literal->value;
            }

            if (literal->type == TokenType::Number)
            {
                return std::stod(literal->value);
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

        // Function call inside an expression
        if (const auto *call =
                dynamic_cast<const CallExpression *>(&expression))
        {

            if (call->name == "view")
            {
                executeCall(*call);
                return std::string("");
            }
        }

        throw std::runtime_error("Invalid expression");
    }

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

        RuntimeValue value = evaluate(*expression.arguments[0]);

        std::visit([](const auto &result)
                   { std::cout << result << '\n'; }, value);
    }

}
