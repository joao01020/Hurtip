
#pragma once

#include "hurtip/ast/ast.hpp"
#include "hurtip/environment/environment.hpp"

#include <filesystem>
#include <functional>
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
        using NativeFunction =
            std::function<RuntimeValue(
                const std::vector<RuntimeValue> &)>;

        using NativeFunctionRegistry =
            std::unordered_map<std::string, NativeFunction>;

        void interpret(
            const std::vector<std::unique_ptr<ASTNode>> &statements);

        void interpret(
            const std::vector<std::unique_ptr<ASTNode>> &statements,
            const std::filesystem::path &sourcePath);

        void registerLibrary(
            const std::string &name,
            NativeFunctionRegistry functions);

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

        // Hurtip module namespaces
        std::unordered_map<std::string, FunctionRegistry> namespaces;

        // Native libraries
        std::unordered_map<
            std::string,
            NativeFunctionRegistry>
            nativeLibraries;

        // Imported library aliases
        std::unordered_map<std::string, std::string> importedLibraries;

        // Module path -> functions declared by that module
        std::unordered_map<std::string, FunctionRegistry> moduleFunctions;

        // Module path -> persistent variable environment
        std::unordered_map<
            std::string,
            std::shared_ptr<Environment>>
            moduleEnvironments;

        // Namespace alias -> module path
        std::unordered_map<std::string, std::string> namespaceModuleKeys;

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

        void executeImport(const ImportStatement &statement);

        RuntimeValue evaluate(const Expression &expression);

        RuntimeValue evaluateBinary(const BinaryExpression &expression);

        RuntimeValue evaluateUnary(const UnaryExpression &expression);

        RuntimeValue executeCall(const CallExpression &expression);
    };
}
