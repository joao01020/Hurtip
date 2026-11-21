
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>
#include <filesystem>

#include "hurtip/lexer/lexer.hpp"
#include "hurtip/parser/parser.hpp"
#include "hurtip/interpreter/interpreter.hpp"
#include "hurtip/libraries/standard_library.hpp"

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: hurtip <file.hurtip>\n";
        return 1;
    }

    const std::string filePath = argv[1];

    std::ifstream file(filePath);

    if (!file.is_open())
    {
        std::cerr << "Error: Could not open file: "
                  << filePath << '\n';
        return 1;
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    const std::string source = buffer.str();

    try
    {
        // Lexer
        hurtip::Lexer lexer(source);
        std::vector<hurtip::Token> tokens = lexer.tokenize();

        // Parser
        hurtip::Parser parser(tokens);
        auto statements = parser.parse();

        // Interpreter
        hurtip::Interpreter interpreter;

        // Register standard libraries
        hurtip::registerStandardLibraries(interpreter);

        interpreter.interpret(
            statements,
            std::filesystem::absolute(filePath));
    }
    catch (const std::exception &error)
    {
        std::cerr << "Hurtip Error: "
                  << error.what() << '\n';

        return 1;
    }

    return 0;
}
