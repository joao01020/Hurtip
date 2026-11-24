
#include "hurtip/interpreter/interpreter.hpp"
#include "hurtip/lexer/lexer.hpp"
#include "hurtip/parser/parser.hpp"

#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <string>

namespace
{
    void runProgram(
        hurtip::Interpreter &interpreter,
        const std::string &source,
        const std::filesystem::path &sourcePath)
    {
        hurtip::Lexer lexer(source);
        const auto tokens = lexer.tokenize();

        hurtip::Parser parser(tokens);
        auto statements = parser.parse();

        interpreter.interpret(statements, sourcePath);
    }

    std::string expectFailure(
        hurtip::Interpreter &interpreter,
        const std::string &source,
        const std::filesystem::path &sourcePath)
    {
        try
        {
            runProgram(interpreter, source, sourcePath);
        }
        catch (const std::exception &error)
        {
            return error.what();
        }

        throw std::runtime_error(
            "Expected the program to fail, but it succeeded.");
    }
}

int main()
{
    try
    {
        const std::filesystem::path projectDirectory =
            HURTIP_PROJECT_SOURCE_DIR;

        const std::filesystem::path sourcePath =
            projectDirectory /
            "tests/modules/modules/errors/recovery_test.hurtip";

        hurtip::Interpreter interpreter;

        const std::string failingSource =
            "load \"runtime_failure.hurtip\" as failed\n";

        // First attempt: the module fails during execution.
        const std::string firstError = expectFailure(
            interpreter,
            failingSource,
            sourcePath);

        if (firstError.find(
                "Undefined variable: undefined_variable") ==
            std::string::npos)
        {
            throw std::runtime_error(
                "Unexpected first error: " + firstError);
        }

        // Second attempt: the same alias must be available again.
        const std::string secondError = expectFailure(
            interpreter,
            failingSource,
            sourcePath);

        if (secondError.find(
                "Undefined variable: undefined_variable") ==
            std::string::npos)
        {
            throw std::runtime_error(
                "Unexpected second error: " + secondError);
        }

        // Third attempt: load a valid module using the same alias.
        const std::string validSource =
            "load \"../state/counter.hurtip\" as failed\n"
            "failed.increment()\n";

        runProgram(interpreter, validSource, sourcePath);

        std::cout << "Module recovery test passed.\n";
        return 0;
    }
    catch (const std::exception &error)
    {
        std::cerr << "Module recovery test failed: "
                  << error.what() << '\n';

        return 1;
    }
}
