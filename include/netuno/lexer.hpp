
#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace netuno
{

    enum class TokenType
    {
        Create,
        Identifier,
        String,
        Number,
        Equal,
        LeftParen,
        RightParen,
        NewLine,
        EndOfFile
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        int line;
    };

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

        char currentChar() const;
        char advance();

        void skipWhitespace();
        void scanToken();
        void scanIdentifier();
        void scanString();
        void scanNumber();
    };

}
