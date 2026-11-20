
#pragma once

#include "hurtip/parser.hpp"

#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace hurtip
{

    using RuntimeValue = std::variant<std::string, double, bool>;

    class Interpreter
    {
    public:
        void interpret(
            const std::vector<std::unique_ptr<ASTNode>> &statements);

    private:
        std::unordered_map<std::string, RuntimeValue> variables;

        void execute(const ASTNode &statement);

        RuntimeValue evaluate(const Expression &expression);

        RuntimeValue evaluateBinary(const BinaryExpression &expression);

        RuntimeValue evaluateUnary(const UnaryExpression &expression);

        void executeCall(const CallExpression &expression);
    };

}
