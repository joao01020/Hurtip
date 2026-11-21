#pragma once

#include "hurtip/token.hpp"

#include <cstddef>
#include <string>
#include <vector>

namespace hurtip
{

    class Lexer
    {
    public:
        explicit Lexer(const std::string &source);

        std::vector<Token> tokenize();

    private:
        std::string source;
        std::vector<Token> tokens;

        std::size_t position = 0;
        int line = 1;
        int column = 1;

        char currentChar() const;
        char peekChar() const;
        char advance();

        void skipWhitespace();
        void skipComment();

        void scanToken();
        void scanIdentifier();
        void scanString();
        void scanNumber();
    };

}