
#pragma once

#include <string>

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
        Comma,
        NewLine,
        EndOfFile
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        int line;
    };

}
