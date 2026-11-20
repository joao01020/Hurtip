
#pragma once

#include <string>

namespace netuno
{

    enum class TokenType
    {
        Create,
        True,
        False,
        If,
        Else,

        // Logical operators
        And,
        Or,
        Not,

        Identifier,
        String,
        Number,

        // Assignment and comparison operators
        Equal,
        EqualEqual,
        BangEqual,
        Greater,
        Less,
        GreaterEqual,
        LessEqual,

        // Arithmetic operators
        Plus,
        Minus,
        Star,
        Slash,

        // Delimiters
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        Comma,

        NewLine,
        EndOfFile
    };

    struct Token
    {
        TokenType type;
        std::string lexeme;
        int line;
        int column;
    };

}
