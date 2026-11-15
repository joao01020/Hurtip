
#include "netuno/lexer.hpp"

#include <cctype>
#include <stdexcept>

namespace netuno
{

    Lexer::Lexer(const std::string &source)
        : source(source)
    {
    }

    char Lexer::currentChar() const
    {
        if (position >= source.length())
        {
            return '\0';
        }

        return source[position];
    }

    char Lexer::advance()
    {
        return source[position++];
    }

    void Lexer::skipWhitespace()
    {
        while (currentChar() == ' ' || currentChar() == '\t' ||
               currentChar() == '\r')
        {
            advance();
        }
    }

    void Lexer::scanIdentifier()
    {
        std::string value;

        while (std::isalnum(static_cast<unsigned char>(currentChar())) ||
               currentChar() == '_')
        {
            value += advance();
        }

        TokenType type = (value == "create")
                             ? TokenType::Create
                             : TokenType::Identifier;

        tokens.push_back({type, value, line});
    }

    void Lexer::scanString()
    {
        advance();

        std::string value;

        while (currentChar() != '"' && currentChar() != '\0')
        {
            if (currentChar() == '\n')
            {
                throw std::runtime_error("Unterminated string");
            }

            value += advance();
        }

        if (currentChar() == '\0')
        {
            throw std::runtime_error("Unterminated string");
        }

        advance();

        tokens.push_back({TokenType::String, value, line});
    }

    void Lexer::scanNumber()
    {
        std::string value;

        while (std::isdigit(static_cast<unsigned char>(currentChar())))
        {
            value += advance();
        }

        tokens.push_back({TokenType::Number, value, line});
    }

    void Lexer::scanToken()
    {
        char character = currentChar();

        if (std::isalpha(static_cast<unsigned char>(character)) ||
            character == '_')
        {
            scanIdentifier();
            return;
        }

        if (std::isdigit(static_cast<unsigned char>(character)))
        {
            scanNumber();
            return;
        }

        switch (character)
        {
        case '"':
            scanString();
            break;

        case '=':
            advance();
            tokens.push_back({TokenType::Equal, "=", line});
            break;

        case '(':
            advance();
            tokens.push_back({TokenType::LeftParen, "(", line});
            break;

        case ')':
            advance();
            tokens.push_back({TokenType::RightParen, ")", line});
            break;

        case '\n':
            advance();
            tokens.push_back({TokenType::NewLine, "\\n", line});
            line++;
            break;

        case ' ':
        case '\t':
        case '\r':
            skipWhitespace();
            break;

        default:
            throw std::runtime_error(
                "Unexpected character: " + std::string(1, character));
        }
    }

    std::vector<Token> Lexer::tokenize()
    {
        while (currentChar() != '\0')
        {
            scanToken();
        }

        tokens.push_back({TokenType::EndOfFile, "", line});

        return tokens;
    }

}
