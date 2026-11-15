
#pragma once

#include "netuno/lexer.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

namespace netuno
{

    // Base class for all syntax tree nodes
    struct ASTNode
    {
        virtual ~ASTNode() = default;
    };

    // Represents a literal value or variable reference
    struct Expression : ASTNode
    {
    };

    // Represents a variable declaration
    struct CreateStatement : ASTNode
    {
        std::string name;
        std::unique_ptr<Expression> value;
    };

    // Represents a function call
    struct CallExpression : Expression
    {
        std::string name;
        std::vector<std::unique_ptr<Expression>> arguments;
    };

    // Represents a string or numeric value
    struct LiteralExpression : Expression
    {
        TokenType type;
        std::string value;
    };

    // Represents a variable reference
    struct IdentifierExpression : Expression
    {
        std::string name;
    };

    class Parser
    {
    public:
        explicit Parser(const std::vector<Token> &tokens);

        std::vector<std::unique_ptr<ASTNode>> parse();

    private:
        const std::vector<Token> &tokens;
        std::size_t position = 0;

        const Token &currentToken() const;
        const Token &advance();

        bool match(TokenType type);
        bool check(TokenType type) const;

        std::unique_ptr<ASTNode> parseStatement();
        std::unique_ptr<CreateStatement> parseCreateStatement();

        std::unique_ptr<Expression> parseExpression();
        std::unique_ptr<Expression> parsePrimaryExpression();
        std::unique_ptr<CallExpression> parseCallExpression();
    };

}
