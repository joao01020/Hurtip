
#pragma once

#include "hurtip/parser.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
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

        void interpret(
            const std::vector<std::unique_ptr<ASTNode>> &statements,
            const std::filesystem::path &sourcePath);

    private:
        std::unordered_map<std::string, RuntimeValue> variables;

        // Module loading
        std::filesystem::path currentFilePath;

        std::unordered_set<std::string> loadedModules;
        std::unordered_set<std::string> loadingModules;

        void execute(const ASTNode &statement);

        void executeStatements(
            const std::vector<std::unique_ptr<ASTNode>> &statements);

        void executeLoad(const LoadStatement &statement);

        RuntimeValue evaluate(const Expression &expression);

        RuntimeValue evaluateBinary(const BinaryExpression &expression);

        RuntimeValue evaluateUnary(const UnaryExpression &expression);

        void executeCall(const CallExpression &expression);
    };

}
