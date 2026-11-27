#pragma once

#include <string>

namespace hurtip
{

    enum class TokenType
    {
        Create,
        Load,
        Import,
        As,

        Function,
        Return,

        True,
        False,
        If,
        Else,
        While,
        For,
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
        PlusPlus,
        Minus,
        Star,
        Slash,

        // Delimiters
        LeftParen,
        RightParen,
        LeftBrace,
        RightBrace,
        LeftBracket,
        RightBracket,
        Comma,
        Dot,
        Semicolon,

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