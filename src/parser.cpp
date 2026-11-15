
#include "netuno/parser.hpp"

#include <stdexcept>

namespace netuno
{

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
                throw std::runtime_error(
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

        throw std::runtime_error(
            "Unexpected token: " + currentToken().lexeme);
    }

    std::unique_ptr<CreateStatement> Parser::parseCreateStatement()
    {
        advance();

        if (!check(TokenType::Identifier))
        {
            throw std::runtime_error(
                "Expected a variable name after 'create'");
        }

        auto statement = std::make_unique<CreateStatement>();

        statement->name = advance().lexeme;

        if (!match(TokenType::Equal))
        {
            throw std::runtime_error(
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

            expression->name = advance().lexeme;

            return expression;
        }

        throw std::runtime_error(
            "Expected an expression, got: " + currentToken().lexeme);
    }

    std::unique_ptr<CallExpression> Parser::parseCallExpression()
    {
        auto expression = std::make_unique<CallExpression>();

        expression->name = advance().lexeme;

        if (!match(TokenType::LeftParen))
        {
            throw std::runtime_error(
                "Expected '(' after function name");
        }

        if (!check(TokenType::RightParen))
        {
            expression->arguments.push_back(parseExpression());
        }

        if (!match(TokenType::RightParen))
        {
            throw std::runtime_error(
                "Expected ')' after function arguments");
        }

        return expression;
    }

}
