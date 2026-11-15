
#pragma once

#include "netuno/parser.hpp"

#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <memory>

namespace netuno
{

    using RuntimeValue = std::variant<std::string, double>;

    class Interpreter
    {
    public:
        void interpret(
            const std::vector<std::unique_ptr<ASTNode>> &statements);

    private:
        std::unordered_map<std::string, RuntimeValue> variables;

        void execute(const ASTNode &statement);

        RuntimeValue evaluate(const Expression &expression);

        void executeCall(const CallExpression &expression);
    };

}
