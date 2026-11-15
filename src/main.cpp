
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <exception>

#include "netuno/lexer.hpp"
#include "netuno/parser.hpp"
#include "netuno/interpreter.hpp"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        std::cerr << "Usage: netuno <file.nt>\n";
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
        netuno::Lexer lexer(source);
        std::vector<netuno::Token> tokens = lexer.tokenize();

        // Parser
        netuno::Parser parser(tokens);
        auto statements = parser.parse();

        // Interpreter
        netuno::Interpreter interpreter;
        interpreter.interpret(statements);
    }
    catch (const std::exception &error)
    {

        std::cerr << "Netuno Error: "
                  << error.what() << '\n';

        return 1;
    }

    return 0;
}
