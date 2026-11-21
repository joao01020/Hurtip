
#pragma once

#include "hurtip/parser/parser.hpp"

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
        using FunctionRegistry =
            std::unordered_map<
                std::string,
                const FunctionDeclaration *>;

        // Variables
        std::unordered_map<std::string, RuntimeValue> variables;

        // Global functions
        FunctionRegistry functions;

        // Namespace -> functions
        std::unordered_map<std::string, FunctionRegistry> namespaces;

        // Module path -> functions declared by that module
        std::unordered_map<std::string, FunctionRegistry> moduleFunctions;

        // Keeps module ASTs alive at stable addresses.
        std::vector<
            std::unique_ptr<std::vector<std::unique_ptr<ASTNode>>>>
            moduleStatements;

        // Module execution context
        std::filesystem::path currentFilePath;
        std::string currentNamespace;

        // Module loading state
        std::unordered_set<std::string> loadedModules;
        std::unordered_set<std::string> loadingModules;

        void execute(const ASTNode &statement);

        void executeStatements(
            const std::vector<std::unique_ptr<ASTNode>> &statements);

        void executeLoad(const LoadStatement &statement);

        RuntimeValue evaluate(const Expression &expression);

        RuntimeValue evaluateBinary(const BinaryExpression &expression);

        RuntimeValue evaluateUnary(const UnaryExpression &expression);

        RuntimeValue executeCall(const CallExpression &expression);
    };

}
