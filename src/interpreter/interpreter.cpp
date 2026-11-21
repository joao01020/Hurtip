
#include "hurtip/interpreter/interpreter.hpp"
#include "interpreter_signals.hpp"

#include "hurtip/lexer/lexer.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
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
    }

    // Interpreter entry points

    void Interpreter::interpret(
        const std::vector<std::unique_ptr<ASTNode>> &statements)
    {
        currentFilePath.clear();
        currentNamespace.clear();
        currentEnvironment = globalEnvironment;

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
            std::filesystem::weakly_canonical(currentFilePath, error);

        if (!error)
        {
            currentFilePath = canonicalPath;
        }

        currentNamespace.clear();
        currentEnvironment = globalEnvironment;

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

            currentEnvironment->define(create->name, value);

            return;
        }

        // Variable assignment

        if (const auto *assignment =
                dynamic_cast<const AssignmentStatement *>(&statement))
        {
            if (!currentEnvironment->contains(assignment->name))
            {
                throw std::runtime_error(
                    "Line " + std::to_string(assignment->line) +
                    ": Undefined variable: " + assignment->name);
            }

            RuntimeValue value = evaluate(*assignment->value);

            currentEnvironment->assign(assignment->name, value);

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
            FunctionRegistry *registry = &functions;

            if (!currentNamespace.empty())
            {
                auto namespaceIterator =
                    namespaces.find(currentNamespace);

                if (namespaceIterator == namespaces.end())
                {
                    throw std::runtime_error(
                        "Line " + std::to_string(function->line) +
                        ": Namespace not initialized: " +
                        currentNamespace);
                }

                registry = &namespaceIterator->second;
            }

            if (registry->find(function->name) != registry->end())
            {
                throw std::runtime_error(
                    "Line " + std::to_string(function->line) +
                    ": Function already declared: " + function->name);
            }

            registry->emplace(function->name, function);

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

            throw detail::ReturnSignal{value};
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

        // Block statement with its own environment

        if (const auto *block =
                dynamic_cast<const BlockStatement *>(&statement))
        {
            const auto previousEnvironment = currentEnvironment;

            currentEnvironment =
                std::make_shared<Environment>(previousEnvironment);

            try
            {
                for (const auto &blockStatement : block->statements)
                {
                    execute(*blockStatement);
                }
            }
            catch (...)
            {
                currentEnvironment = previousEnvironment;
                throw;
            }

            currentEnvironment = previousEnvironment;

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
            std::filesystem::weakly_canonical(modulePath, error);

        if (!error)
        {
            modulePath = canonicalPath;
        }

        const std::string moduleKey = modulePath.string();

        const std::string alias =
            statement.alias.empty()
                ? modulePath.stem().string()
                : statement.alias;

        // A namespace cannot be reused for a different module.

        auto existingNamespace = namespaces.find(alias);

        if (existingNamespace != namespaces.end())
        {
            auto existingModule = moduleFunctions.find(moduleKey);

            if (existingModule == moduleFunctions.end() ||
                existingNamespace->second != existingModule->second)
            {
                throw std::runtime_error(
                    "Line " + std::to_string(statement.line) +
                    ": Namespace already declared: " + alias);
            }
        }

        // Reuse an already loaded module.

        if (loadedModules.find(moduleKey) != loadedModules.end())
        {
            namespaces[alias] = moduleFunctions.at(moduleKey);

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

        const std::string previousNamespace =
            currentNamespace;

        const auto previousEnvironment =
            currentEnvironment;

        // Create the namespace before executing the module.

        namespaces.emplace(alias, FunctionRegistry{});

        try
        {
            Lexer lexer(source);

            std::vector<Token> tokens = lexer.tokenize();

            Parser parser(tokens);

            auto statements = parser.parse();

            // Keep the module AST alive.

            auto module = std::make_unique<
                std::vector<std::unique_ptr<ASTNode>>>(
                std::move(statements));

            const auto *modulePointer = module.get();

            moduleStatements.push_back(std::move(module));

            // Execute the module in its own context.

            currentFilePath = modulePath;
            currentNamespace = alias;
            currentEnvironment = globalEnvironment;

            executeStatements(*modulePointer);

            // Save the module's function registry.

            moduleFunctions[moduleKey] = namespaces.at(alias);

            currentFilePath = previousFilePath;
            currentNamespace = previousNamespace;
            currentEnvironment = previousEnvironment;

            loadingModules.erase(moduleKey);
            loadedModules.insert(moduleKey);
        }
        catch (...)
        {
            currentFilePath = previousFilePath;
            currentNamespace = previousNamespace;
            currentEnvironment = previousEnvironment;

            loadingModules.erase(moduleKey);

            namespaces.erase(alias);

            throw;
        }
    }
}
