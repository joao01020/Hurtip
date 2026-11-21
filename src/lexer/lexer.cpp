#include "hurtip/lexer/lexer.hpp"

#include <cctype>
#include <stdexcept>

namespace hurtip
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

    char Lexer::peekChar() const
    {
        if (position + 1 >= source.length())
        {
            return '\0';
        }

        return source[position + 1];
    }

    char Lexer::advance()
    {
        char character = source[position++];

        if (character == '\n')
        {
            line++;
            column = 1;
        }
        else
        {
            column++;
        }

        return character;
    }

    void Lexer::skipWhitespace()
    {
        while (currentChar() == ' ' ||
               currentChar() == '\t' ||
               currentChar() == '\r')
        {
            advance();
        }
    }

    void Lexer::skipComment()
    {
        while (currentChar() != '\n' &&
               currentChar() != '\0')
        {
            advance();
        }
    }

    void Lexer::scanIdentifier()
    {
        int tokenLine = line;
        int tokenColumn = column;

        std::string value;

        while (std::isalnum(static_cast<unsigned char>(currentChar())) ||
               currentChar() == '_')
        {
            value += advance();
        }

        TokenType type = TokenType::Identifier;

        if (value == "create")
        {
            type = TokenType::Create;
        }
        else if (value == "load")
        {
            type = TokenType::Load;
        }
        else if (value == "as")
        {
            type = TokenType::As;
        }
        else if (value == "function")
        {
            type = TokenType::Function;
        }
        else if (value == "return")
        {
            type = TokenType::Return;
        }
        else if (value == "true")
        {
            type = TokenType::True;
        }
        else if (value == "false")
        {
            type = TokenType::False;
        }
        else if (value == "if")
        {
            type = TokenType::If;
        }
        else if (value == "else")
        {
            type = TokenType::Else;
        }
        else if (value == "while")
        {
            type = TokenType::While;
        }
        else if (value == "break")
        {
            type = TokenType::Break;
        }
        else if (value == "continue")
        {
            type = TokenType::Continue;
        }
        else if (value == "and")
        {
            type = TokenType::And;
        }
        else if (value == "or")
        {
            type = TokenType::Or;
        }
        else if (value == "not")
        {
            type = TokenType::Not;
        }

        tokens.push_back({type, value, tokenLine, tokenColumn});
    }

    void Lexer::scanString()
    {
        int tokenLine = line;
        int tokenColumn = column;

        advance();

        std::string value;

        while (currentChar() != '"' && currentChar() != '\0')
        {
            if (currentChar() == '\n')
            {
                throw std::runtime_error(
                    "Unterminated string at line " +
                    std::to_string(tokenLine) +
                    ", column " +
                    std::to_string(tokenColumn));
            }

            value += advance();
        }

        if (currentChar() == '\0')
        {
            throw std::runtime_error(
                "Unterminated string at line " +
                std::to_string(tokenLine) +
                ", column " +
                std::to_string(tokenColumn));
        }

        advance();

        tokens.push_back({TokenType::String,
                          value,
                          tokenLine,
                          tokenColumn});
    }

    void Lexer::scanNumber()
    {
        int tokenLine = line;
        int tokenColumn = column;

        std::string value;

        while (std::isdigit(static_cast<unsigned char>(currentChar())))
        {
            value += advance();
        }

        tokens.push_back({TokenType::Number,
                          value,
                          tokenLine,
                          tokenColumn});
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

        int tokenLine = line;
        int tokenColumn = column;

        switch (character)
        {
        case '"':
            scanString();
            break;

        case '=':
            advance();

            if (currentChar() == '=')
            {
                advance();

                tokens.push_back({TokenType::EqualEqual,
                                  "==",
                                  tokenLine,
                                  tokenColumn});
            }
            else
            {
                tokens.push_back({TokenType::Equal,
                                  "=",
                                  tokenLine,
                                  tokenColumn});
            }
            break;

        case '!':
            advance();

            if (currentChar() == '=')
            {
                advance();

                tokens.push_back({TokenType::BangEqual,
                                  "!=",
                                  tokenLine,
                                  tokenColumn});
            }
            else
            {
                throw std::runtime_error(
                    "Unexpected character '!' at line " +
                    std::to_string(tokenLine) +
                    ", column " +
                    std::to_string(tokenColumn));
            }
            break;

        case '>':
            advance();

            if (currentChar() == '=')
            {
                advance();

                tokens.push_back({TokenType::GreaterEqual,
                                  ">=",
                                  tokenLine,
                                  tokenColumn});
            }
            else
            {
                tokens.push_back({TokenType::Greater,
                                  ">",
                                  tokenLine,
                                  tokenColumn});
            }
            break;

        case '<':
            advance();

            if (currentChar() == '=')
            {
                advance();

                tokens.push_back({TokenType::LessEqual,
                                  "<=",
                                  tokenLine,
                                  tokenColumn});
            }
            else
            {
                tokens.push_back({TokenType::Less,
                                  "<",
                                  tokenLine,
                                  tokenColumn});
            }
            break;

        case '+':
            advance();

            tokens.push_back({TokenType::Plus,
                              "+",
                              tokenLine,
                              tokenColumn});
            break;

        case '-':
            advance();

            tokens.push_back({TokenType::Minus,
                              "-",
                              tokenLine,
                              tokenColumn});
            break;

        case '*':
            advance();

            tokens.push_back({TokenType::Star,
                              "*",
                              tokenLine,
                              tokenColumn});
            break;

        case '/':
            if (peekChar() == '/')
            {
                advance();
                advance();

                skipComment();
            }
            else
            {
                advance();

                tokens.push_back({TokenType::Slash,
                                  "/",
                                  tokenLine,
                                  tokenColumn});
            }
            break;

        case '(':
            advance();

            tokens.push_back({TokenType::LeftParen,
                              "(",
                              tokenLine,
                              tokenColumn});
            break;

        case ')':
            advance();

            tokens.push_back({TokenType::RightParen,
                              ")",
                              tokenLine,
                              tokenColumn});
            break;

        case '{':
            advance();

            tokens.push_back({TokenType::LeftBrace,
                              "{",
                              tokenLine,
                              tokenColumn});
            break;

        case '}':
            advance();

            tokens.push_back({TokenType::RightBrace,
                              "}",
                              tokenLine,
                              tokenColumn});
            break;

        case ',':
            advance();

            tokens.push_back({TokenType::Comma,
                              ",",
                              tokenLine,
                              tokenColumn});
            break;

        case '.':
            advance();

            tokens.push_back({TokenType::Dot,
                              ".",
                              tokenLine,
                              tokenColumn});
            break;

        case '\n':
            advance();

            tokens.push_back({TokenType::NewLine,
                              "\n",
                              tokenLine,
                              tokenColumn});
            break;

        case ' ':
        case '\t':
        case '\r':
            skipWhitespace();
            break;

        default:
            throw std::runtime_error(
                "Unexpected character '" +
                std::string(1, character) +
                "' at line " +
                std::to_string(tokenLine) +
                ", column " +
                std::to_string(tokenColumn));
        }
    }

    std::vector<Token> Lexer::tokenize()
    {
        while (currentChar() != '\0')
        {
            scanToken();
        }

        tokens.push_back({TokenType::EndOfFile,
                          "",
                          line,
                          column});

        return tokens;
    }

}