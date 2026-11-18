
#include "netuno/parser.hpp"

#include <stdexcept>
#include <string>

namespace netuno
{

    static std::runtime_error parserError(
        const Token &token,
        const std::string &message)
    {
        return std::runtime_error(
            "Line " + std::to_string(token.line) + ": " + message);
    }

    Parser::Parser(const std::vector<Token> &tokens)
        : tokens(tokens)
    {
    }

    const Token &Parser::currentToken() const
    {
        return tokens[position];
    }

    const Token &Parser::advance()
    {
        const Token &token = currentToken();

        if (token.type != TokenType::EndOfFile)
        {
            position++;
        }

        return token;
    }

    bool Parser::check(TokenType type) const
    {
        return currentToken().type == type;
    }

    bool Parser::match(TokenType type)
    {
        if (!check(type))
        {
            return false;
        }

        advance();
        return true;
    }

    std::vector<std::unique_ptr<ASTNode>> Parser::parse()
    {
        std::vector<std::unique_ptr<ASTNode>> statements;

        while (!check(TokenType::EndOfFile))
        {
            if (match(TokenType::NewLine))
            {
                continue;
            }

            statements.push_back(parseStatement());

            if (!check(TokenType::NewLine) &&
                !check(TokenType::EndOfFile))
            {
                throw parserError(
                    currentToken(),
                    "Expected a new line after statement");
            }
        }

        return statements;
    }

    std::unique_ptr<ASTNode> Parser::parseStatement()
    {
        if (check(TokenType::Create))
        {
            return parseCreateStatement();
        }

        if (check(TokenType::Identifier))
        {
            return parseExpression();
        }

        throw parserError(
            currentToken(),
            "Unexpected token: " + currentToken().lexeme);
    }

    std::unique_ptr<CreateStatement> Parser::parseCreateStatement()
    {
        const Token &createToken = advance();

        if (!check(TokenType::Identifier))
        {
            throw parserError(
                currentToken(),
                "Expected a variable name after 'create'");
        }

        auto statement = std::make_unique<CreateStatement>();

        statement->line = createToken.line;
        statement->name = advance().lexeme;

        if (!match(TokenType::Equal))
        {
            throw parserError(
                currentToken(),
                "Expected '=' after variable name");
        }

        statement->value = parseExpression();

        return statement;
    }

    std::unique_ptr<Expression> Parser::parseExpression()
    {
        return parsePrimaryExpression();
    }

    std::unique_ptr<Expression> Parser::parsePrimaryExpression()
    {
        if (check(TokenType::String) || check(TokenType::Number))
        {
            auto expression = std::make_unique<LiteralExpression>();

            const Token &token = advance();

            expression->line = token.line;
            expression->type = token.type;
            expression->value = token.lexeme;

            return expression;
        }

        if (check(TokenType::Identifier))
        {
            const bool isCall =
                position + 1 < tokens.size() &&
                tokens[position + 1].type == TokenType::LeftParen;

            if (isCall)
            {
                return parseCallExpression();
            }

            auto expression = std::make_unique<IdentifierExpression>();

            const Token &token = advance();

            expression->line = token.line;
            expression->name = token.lexeme;

            return expression;
        }

        throw parserError(
            currentToken(),
            "Expected an expression, got: " + currentToken().lexeme);
    }

    std::unique_ptr<CallExpression> Parser::parseCallExpression()
    {
        auto expression = std::make_unique<CallExpression>();

        const Token &nameToken = advance();

        expression->line = nameToken.line;
        expression->name = nameToken.lexeme;

        if (!match(TokenType::LeftParen))
        {
            throw parserError(
                currentToken(),
                "Expected '(' after function name");
        }

        if (!check(TokenType::RightParen))
        {
            expression->arguments.push_back(parseExpression());

            while (match(TokenType::Comma))
            {
                expression->arguments.push_back(parseExpression());
            }
        }

        if (!match(TokenType::RightParen))
        {
            throw parserError(
                currentToken(),
                "Expected ')' after function arguments");
        }

        return expression;
    }

}
