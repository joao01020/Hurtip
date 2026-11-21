#pragma once

#include <string>

namespace hurtip
{

    enum class TokenType
    {
        Create,
        Load,
        As,

        Function,
        Return,

        True,
        False,
        If,
        Else,
        While,
        Break,
        Continue,

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
        Dot,

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