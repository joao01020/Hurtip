
#include "hurtip/lexer/lexer.hpp"

#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    using hurtip::Lexer;
    using hurtip::Token;
    using hurtip::TokenType;

    int passed = 0;
    int failed = 0;

    struct ExpectedToken
    {
        TokenType type;
        std::string lexeme;
        int line;
        int column;
    };

    void check(
        const std::string &name,
        const std::string &source,
        const std::vector<ExpectedToken> &expected)
    {
        try
        {
            Lexer lexer(source);
            std::vector<Token> actual = lexer.tokenize();

            if (actual.size() != expected.size())
            {
                throw std::runtime_error(
                    "Expected " + std::to_string(expected.size()) +
                    " tokens, got " + std::to_string(actual.size()));
            }

            for (std::size_t i = 0; i < expected.size(); ++i)
            {
                if (actual[i].type != expected[i].type ||
                    actual[i].lexeme != expected[i].lexeme ||
                    actual[i].line != expected[i].line ||
                    actual[i].column != expected[i].column)
                {
                    throw std::runtime_error(
                        "Token " + std::to_string(i) +
                        " does not match expected value");
                }
            }

            ++passed;
            std::cout << "[PASS] " << name << '\n';
        }
        catch (const std::exception &error)
        {
            ++failed;
            std::cout << "[FAIL] " << name
                      << ": " << error.what() << '\n';
        }
    }

    void checkError(
        const std::string &name,
        const std::string &source,
        const std::string &expectedMessage)
    {
        try
        {
            Lexer lexer(source);
            lexer.tokenize();

            ++failed;
            std::cout << "[FAIL] " << name
                      << ": expected an exception, but none was thrown\n";
        }
        catch (const std::exception &error)
        {
            if (std::string(error.what()).find(expectedMessage) !=
                std::string::npos)
            {
                ++passed;
                std::cout << "[PASS] " << name << '\n';
            }
            else
            {
                ++failed;
                std::cout << "[FAIL] " << name
                          << ": unexpected error: "
                          << error.what() << '\n';
            }
        }
    }

    void testKeywords()
    {
        check(
            "keywords",
            "create load import as function return true false if else while break continue and or not",
            {{TokenType::Create, "create", 1, 1},
             {TokenType::Load, "load", 1, 8},
             {TokenType::Import, "import", 1, 13},
             {TokenType::As, "as", 1, 20},
             {TokenType::Function, "function", 1, 23},
             {TokenType::Return, "return", 1, 32},
             {TokenType::True, "true", 1, 39},
             {TokenType::False, "false", 1, 44},
             {TokenType::If, "if", 1, 50},
             {TokenType::Else, "else", 1, 53},
             {TokenType::While, "while", 1, 58},
             {TokenType::Break, "break", 1, 64},
             {TokenType::Continue, "continue", 1, 70},
             {TokenType::And, "and", 1, 79},
             {TokenType::Or, "or", 1, 83},
             {TokenType::Not, "not", 1, 86},
             {TokenType::EndOfFile, "", 1, 89}});
    }

    void testIdentifiers()
    {
        check(
            "identifiers",
            "name user_name _private value123 imported",
            {{TokenType::Identifier, "name", 1, 1},
             {TokenType::Identifier, "user_name", 1, 6},
             {TokenType::Identifier, "_private", 1, 16},
             {TokenType::Identifier, "value123", 1, 25},
             {TokenType::Identifier, "imported", 1, 34},
             {TokenType::EndOfFile, "", 1, 42}});
    }

    void testImportStatementTokens()
    {
        check(
            "import statement tokens",
            "import \"math\"",
            {{TokenType::Import, "import", 1, 1},
             {TokenType::String, "math", 1, 8},
             {TokenType::EndOfFile, "", 1, 14}});

        check(
            "import with alias tokens",
            "import \"math\" as mathematics",
            {{TokenType::Import, "import", 1, 1},
             {TokenType::String, "math", 1, 8},
             {TokenType::As, "as", 1, 15},
             {TokenType::Identifier, "mathematics", 1, 18},
             {TokenType::EndOfFile, "", 1, 29}});
    }

    void testLiterals()
    {
        check(
            "numbers and strings",
            "123 0 98765 \"Hello Hurtip\" \"test\"",
            {{TokenType::Number, "123", 1, 1},
             {TokenType::Number, "0", 1, 5},
             {TokenType::Number, "98765", 1, 7},
             {TokenType::String, "Hello Hurtip", 1, 13},
             {TokenType::String, "test", 1, 28},
             {TokenType::EndOfFile, "", 1, 34}});
    }

    void testOperators()
    {
        check(
            "operators",
            "= == != > < >= <= + - * /",
            {{TokenType::Equal, "=", 1, 1},
             {TokenType::EqualEqual, "==", 1, 3},
             {TokenType::BangEqual, "!=", 1, 6},
             {TokenType::Greater, ">", 1, 9},
             {TokenType::Less, "<", 1, 11},
             {TokenType::GreaterEqual, ">=", 1, 13},
             {TokenType::LessEqual, "<=", 1, 16},
             {TokenType::Plus, "+", 1, 19},
             {TokenType::Minus, "-", 1, 21},
             {TokenType::Star, "*", 1, 23},
             {TokenType::Slash, "/", 1, 25},
             {TokenType::EndOfFile, "", 1, 26}});
    }

    void testDelimiters()
    {
        check(
            "delimiters",
            "( ) { } , .",
            {{TokenType::LeftParen, "(", 1, 1},
             {TokenType::RightParen, ")", 1, 3},
             {TokenType::LeftBrace, "{", 1, 5},
             {TokenType::RightBrace, "}", 1, 7},
             {TokenType::Comma, ",", 1, 9},
             {TokenType::Dot, ".", 1, 11},
             {TokenType::EndOfFile, "", 1, 12}});
    }

    void testNewLines()
    {
        check(
            "newlines and token positions",
            "create value = 10\nview(value)",
            {{TokenType::Create, "create", 1, 1},
             {TokenType::Identifier, "value", 1, 8},
             {TokenType::Equal, "=", 1, 14},
             {TokenType::Number, "10", 1, 16},
             {TokenType::NewLine, "\n", 1, 18},
             {TokenType::Identifier, "view", 2, 1},
             {TokenType::LeftParen, "(", 2, 5},
             {TokenType::Identifier, "value", 2, 6},
             {TokenType::RightParen, ")", 2, 11},
             {TokenType::EndOfFile, "", 2, 12}});
    }

    void testComments()
    {
        check(
            "comments",
            "create value = 10 // ignored comment\nview(value)",
            {{TokenType::Create, "create", 1, 1},
             {TokenType::Identifier, "value", 1, 8},
             {TokenType::Equal, "=", 1, 14},
             {TokenType::Number, "10", 1, 16},
             {TokenType::NewLine, "\n", 1, 37},
             {TokenType::Identifier, "view", 2, 1},
             {TokenType::LeftParen, "(", 2, 5},
             {TokenType::Identifier, "value", 2, 6},
             {TokenType::RightParen, ")", 2, 11},
             {TokenType::EndOfFile, "", 2, 12}});
    }

    void testWhitespace()
    {
        check(
            "whitespace",
            "  create\tvalue\r\n",
            {{TokenType::Create, "create", 1, 3},
             {TokenType::Identifier, "value", 1, 10},
             {TokenType::NewLine, "\n", 1, 16},
             {TokenType::EndOfFile, "", 2, 1}});
    }

    void testEmptySource()
    {
        check(
            "empty source",
            "",
            {{TokenType::EndOfFile, "", 1, 1}});
    }

    void testInvalidCharacters()
    {
        checkError(
            "invalid character",
            "@",
            "Unexpected character '@' at line 1, column 1");

        checkError(
            "standalone exclamation mark",
            "!",
            "Unexpected character '!' at line 1, column 1");
    }

    void testUnterminatedStrings()
    {
        checkError(
            "unterminated string at end of file",
            "\"Hello",
            "Unterminated string at line 1, column 1");

        checkError(
            "unterminated string at newline",
            "\"Hello\nworld\"",
            "Unterminated string at line 1, column 1");
    }
}

int main()
{
    std::cout << "Running Hurtip Lexer tests...\n\n";

    testKeywords();
    testIdentifiers();
    testImportStatementTokens();
    testLiterals();
    testOperators();
    testDelimiters();
    testNewLines();
    testComments();
    testWhitespace();
    testEmptySource();
    testInvalidCharacters();
    testUnterminatedStrings();

    std::cout << "\n-----------------------------\n";
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';
    std::cout << "-----------------------------\n";

    return failed == 0 ? 0 : 1;
}
