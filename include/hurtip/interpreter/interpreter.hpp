
#pragma once

#include "hurtip/parser/parser.hpp"
#include "hurtip/environment/environment.hpp"

#include <filesystem>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

namespace hurtip
{
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

        // Variable environments
        std::shared_ptr<Environment> globalEnvironment =
            std::make_shared<Environment>();

        std::shared_ptr<Environment> currentEnvironment =
            globalEnvironment;

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
