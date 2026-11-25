#include "hurtip/interpreter/interpreter.hpp"
#include "hurtip/parser/parser.hpp"
#include "interpreter_signals.hpp"

#include "hurtip/lexer/lexer.hpp"

#include <cmath>
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
} // namespace

// Interpreter entry points

void Interpreter::interpret(const std::vector<std::unique_ptr<ASTNode>>& statements)
{
    currentFilePath.clear();
    currentNamespace.clear();
    currentEnvironment = globalEnvironment;

    executeStatements(statements);
}

void Interpreter::interpret(const std::vector<std::unique_ptr<ASTNode>>& statements,
                            const std::filesystem::path& sourcePath)
{
    currentFilePath = std::filesystem::absolute(sourcePath).lexically_normal();

    std::error_code error;

    std::filesystem::path canonicalPath = std::filesystem::weakly_canonical(currentFilePath, error);

    if (!error)
    {
        currentFilePath = canonicalPath;
    }

    currentNamespace.clear();
    currentEnvironment = globalEnvironment;

    executeStatements(statements);
}

// Native library registration

void Interpreter::registerLibrary(const std::string& name, NativeFunctionRegistry nativeFunctions)
{
    if (name.empty())
    {
        throw std::runtime_error("Library name cannot be empty");
    }

    if (nativeFunctions.empty())
    {
        throw std::runtime_error("Library cannot be empty: " + name);
    }

    for (const auto& function : nativeFunctions)
    {
        if (function.first.empty() || !function.second)
        {
            throw std::runtime_error("Invalid native function in library: " + name);
        }
    }

    if (nativeLibraries.find(name) != nativeLibraries.end())
    {
        throw std::runtime_error("Library already registered: " + name);
    }

    nativeLibraries.emplace(name, std::move(nativeFunctions));
}

// Statement execution

void Interpreter::executeStatements(const std::vector<std::unique_ptr<ASTNode>>& statements)
{
    for (const auto& statement : statements)
    {
        try
        {
            execute(*statement);
        }
        catch (const BreakSignal& signal)
        {
            throw std::runtime_error("Line " + std::to_string(signal.line) +
                                     ": 'break' can only be used inside a loop");
        }
        catch (const ContinueSignal& signal)
        {
            throw std::runtime_error("Line " + std::to_string(signal.line) +
                                     ": 'continue' can only be used inside a loop");
        }
    }
}

void Interpreter::execute(const ASTNode& statement)
{
    // Variable declaration

    // Variable declaration
    if (const auto* create = dynamic_cast<const CreateStatement*>(&statement))
    {
        RuntimeValue value = evaluate(*create->value);

        if (!currentEnvironment->define(create->name, value))
        {
            throw std::runtime_error("Line " + std::to_string(create->line) +
                                     ": Variable already declared: " + create->name);
        }

        return;
    }

    // Variable assignment

    if (const auto* assignment = dynamic_cast<const AssignmentStatement*>(&statement))
    {
        // Assignment using an expression target.

        if (assignment->target)
        {
            // Direct variable assignment.

            if (const auto* identifier =
                    dynamic_cast<const IdentifierExpression*>(assignment->target.get()))
            {
                if (!currentEnvironment->contains(identifier->name))
                {
                    throw std::runtime_error("Line " + std::to_string(assignment->line) +
                                             ": Undefined variable: " + identifier->name);
                }

                RuntimeValue value = evaluate(*assignment->value);

                currentEnvironment->assign(identifier->name, value);

                return;
            }

            // Array element assignment.

            if (const auto* index = dynamic_cast<const IndexExpression*>(assignment->target.get()))
            {
                RuntimeValue object = evaluate(*index->object);
                RuntimeValue indexValue = evaluate(*index->index);

                const auto* array = std::get_if<std::shared_ptr<ArrayValue>>(&object);

                if (!array || !*array)
                {
                    throw std::runtime_error("Line " + std::to_string(index->line) +
                                             ": Index assignment requires an array");
                }

                const auto* number = std::get_if<double>(&indexValue);

                if (!number)
                {
                    throw std::runtime_error("Line " + std::to_string(index->line) +
                                             ": Array index must be a number");
                }

                if (!std::isfinite(*number) || *number < 0.0 || std::floor(*number) != *number)
                {
                    throw std::runtime_error("Line " + std::to_string(index->line) +
                                             ": Array index must be a non-negative integer");
                }

                const std::size_t arrayIndex = static_cast<std::size_t>(*number);

                if (arrayIndex >= (*array)->elements.size())
                {
                    (*array)->elements.resize(arrayIndex + 1, 0.0);
                }

                RuntimeValue value = evaluate(*assignment->value);

                (*array)->elements[arrayIndex] = value;

                return;
            }

            throw std::runtime_error("Line " + std::to_string(assignment->line) +
                                     ": Invalid assignment target");
        }

        // Legacy assignment support.

        if (!currentEnvironment->contains(assignment->name))
        {
            throw std::runtime_error("Line " + std::to_string(assignment->line) +
                                     ": Undefined variable: " + assignment->name);
        }

        RuntimeValue value = evaluate(*assignment->value);

        currentEnvironment->assign(assignment->name, value);

        return;
    }

    // Load statement

    if (const auto* load = dynamic_cast<const LoadStatement*>(&statement))
    {
        executeLoad(*load);

        return;
    }

    // Import statement

    if (const auto* import = dynamic_cast<const ImportStatement*>(&statement))
    {
        executeImport(*import);

        return;
    }

    // Function declaration

    if (const auto* function = dynamic_cast<const FunctionDeclaration*>(&statement))
    {
        FunctionRegistry* registry = &functions;

        if (!currentNamespace.empty())
        {
            auto namespaceIterator = namespaces.find(currentNamespace);

            if (namespaceIterator == namespaces.end())
            {
                throw std::runtime_error("Line " + std::to_string(function->line) +
                                         ": Namespace not initialized: " + currentNamespace);
            }

            registry = &namespaceIterator->second;
        }

        if (registry->find(function->name) != registry->end())
        {
            throw std::runtime_error("Line " + std::to_string(function->line) +
                                     ": Function already declared: " + function->name);
        }

        registry->emplace(function->name, function);

        return;
    }

    // Return statement

    if (const auto* returnStatement = dynamic_cast<const ReturnStatement*>(&statement))
    {
        RuntimeValue value = std::string("");

        if (returnStatement->value)
        {
            value = evaluate(*returnStatement->value);
        }

        throw detail::ReturnSignal{value};
    }

    // If statement

    if (const auto* ifStatement = dynamic_cast<const IfStatement*>(&statement))
    {
        RuntimeValue condition = evaluate(*ifStatement->condition);

        const bool* boolean = std::get_if<bool>(&condition);

        if (!boolean)
        {
            throw std::runtime_error("Line " + std::to_string(ifStatement->line) +
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

    if (const auto* breakStatement = dynamic_cast<const BreakStatement*>(&statement))
    {
        throw BreakSignal{breakStatement->line};
    }

    // Continue statement

    if (const auto* continueStatement = dynamic_cast<const ContinueStatement*>(&statement))
    {
        throw ContinueSignal{continueStatement->line};
    }

    // While statement

    if (const auto* whileStatement = dynamic_cast<const WhileStatement*>(&statement))
    {
        while (true)
        {
            RuntimeValue condition = evaluate(*whileStatement->condition);

            const bool* boolean = std::get_if<bool>(&condition);

            if (!boolean)
            {
                throw std::runtime_error("Line " + std::to_string(whileStatement->line) +
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
            catch (const ContinueSignal&)
            {
                continue;
            }
            catch (const BreakSignal&)
            {
                break;
            }
        }

        return;
    }

    // Block statement with its own environment

    if (const auto* block = dynamic_cast<const BlockStatement*>(&statement))
    {
        const auto previousEnvironment = currentEnvironment;

        currentEnvironment = std::make_shared<Environment>(previousEnvironment);

        try
        {
            for (const auto& blockStatement : block->statements)
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

    if (const auto* call = dynamic_cast<const CallExpression*>(&statement))
    {
        executeCall(*call);

        return;
    }

    throw std::runtime_error("Unknown statement");
}

// Module loading

void Interpreter::executeLoad(const LoadStatement& statement)
{
    std::filesystem::path modulePath(statement.path);

    if (modulePath.extension() != ".hurtip")
    {
        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Modules must use the .hurtip extension");
    }

    // Resolve paths relative to the file containing the load statement.

    if (modulePath.is_relative())
    {
        if (!currentFilePath.empty())
        {
            modulePath = currentFilePath.parent_path() / modulePath;
        }
        else
        {
            modulePath = std::filesystem::current_path() / modulePath;
        }
    }

    modulePath = std::filesystem::absolute(modulePath).lexically_normal();

    std::error_code error;

    std::filesystem::path canonicalPath = std::filesystem::weakly_canonical(modulePath, error);

    if (!error)
    {
        modulePath = canonicalPath;
    }

    const std::string moduleKey = modulePath.string();

    const std::string alias =
        statement.alias.empty() ? modulePath.stem().string() : statement.alias;

    // A module cannot reuse an alias assigned to a native library.

    auto existingImport = importedLibraries.find(alias);

    if (existingImport != importedLibraries.end())
    {
        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Namespace already imported: " + alias);
    }

    // A namespace cannot be reused for a different module.

    auto existingNamespace = namespaces.find(alias);

    if (existingNamespace != namespaces.end())
    {
        auto existingModule = moduleFunctions.find(moduleKey);

        if (existingModule == moduleFunctions.end() ||
            existingNamespace->second != existingModule->second)
        {
            throw std::runtime_error("Line " + std::to_string(statement.line) +
                                     ": Namespace already declared: " + alias);
        }
    }

    // Reuse an already loaded module.

    if (loadedModules.find(moduleKey) != loadedModules.end())
    {
        namespaces[alias] = moduleFunctions.at(moduleKey);
        namespaceModuleKeys[alias] = moduleKey;

        return;
    }

    // Detect circular dependencies.

    if (loadingModules.find(moduleKey) != loadingModules.end())
    {
        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Circular module dependency: " + moduleKey);
    }

    std::ifstream file(modulePath);

    if (!file.is_open())
    {
        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Could not open module: " + moduleKey);
    }

    std::stringstream buffer;

    buffer << file.rdbuf();

    if (file.bad())
    {
        throw std::runtime_error("Could not read module: " + moduleKey);
    }

    const std::string source = buffer.str();

    loadingModules.insert(moduleKey);

    const std::filesystem::path previousFilePath = currentFilePath;

    const std::string previousNamespace = currentNamespace;

    const auto previousEnvironment = currentEnvironment;

    // Create the namespace and persistent environment.

    namespaces.emplace(alias, FunctionRegistry{});

    namespaceModuleKeys[alias] = moduleKey;

    moduleEnvironments[moduleKey] = std::make_shared<Environment>(globalEnvironment);

    try
    {
        Lexer lexer(source);

        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);

        auto statements = parser.parse();

        // Keep the module AST locally until execution succeeds.

        auto module =
            std::make_unique<std::vector<std::unique_ptr<ASTNode>>>(std::move(statements));

        const auto* modulePointer = module.get();

        // Execute the module in its own context.

        currentFilePath = modulePath;
        currentNamespace = alias;
        currentEnvironment = moduleEnvironments.at(moduleKey);

        executeStatements(*modulePointer);

        // Save the module's function registry.

        moduleFunctions[moduleKey] = namespaces.at(alias);

        // Keep the successfully executed module AST alive.

        moduleStatements.push_back(std::move(module));

        // Restore the previous execution context.

        currentFilePath = previousFilePath;
        currentNamespace = previousNamespace;
        currentEnvironment = previousEnvironment;

        loadingModules.erase(moduleKey);
        loadedModules.insert(moduleKey);
    }
    catch (...)
    {
        // Restore the previous execution context.

        currentFilePath = previousFilePath;
        currentNamespace = previousNamespace;
        currentEnvironment = previousEnvironment;

        loadingModules.erase(moduleKey);

        moduleFunctions.erase(moduleKey);
        namespaces.erase(alias);
        namespaceModuleKeys.erase(alias);
        moduleEnvironments.erase(moduleKey);

        throw;
    }
}

// Native library importing

void Interpreter::executeImport(const ImportStatement& statement)
{
    auto library = nativeLibraries.find(statement.name);

    if (library == nativeLibraries.end())
    {
        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Unknown native library: " + statement.name);
    }

    const std::string alias = statement.alias.empty() ? statement.name : statement.alias;

    // A native library cannot reuse an alias assigned to a module.

    if (namespaces.find(alias) != namespaces.end())
    {
        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Namespace already declared: " + alias);
    }

    auto existingImport = importedLibraries.find(alias);

    if (existingImport != importedLibraries.end())
    {
        if (existingImport->second == statement.name)
        {
            return;
        }

        throw std::runtime_error("Line " + std::to_string(statement.line) +
                                 ": Namespace already imported: " + alias);
    }

    importedLibraries.emplace(alias, statement.name);
}
} // namespace hurtip
