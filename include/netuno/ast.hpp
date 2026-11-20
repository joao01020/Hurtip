
#pragma once

#include "netuno/token.hpp"

#include <memory>
#include <string>
#include <vector>

namespace netuno
{

    struct ASTNode
    {
        int line = 1;

        virtual ~ASTNode() = default;
    };

    struct Expression : ASTNode
    {
        virtual ~Expression() = default;
    };

    struct CreateStatement : ASTNode
    {
        std::string name;
        std::unique_ptr<Expression> value;
    };

    struct AssignmentStatement : ASTNode
    {
        std::string name;
        std::unique_ptr<Expression> value;
    };

    struct BlockStatement : ASTNode
    {
        std::vector<std::unique_ptr<ASTNode>> statements;
    };

    struct IfStatement : ASTNode
    {
        std::unique_ptr<Expression> condition;
        std::unique_ptr<BlockStatement> thenBranch;
        std::unique_ptr<BlockStatement> elseBranch;
    };

    struct WhileStatement : ASTNode
    {
        std::unique_ptr<Expression> condition;
        std::unique_ptr<BlockStatement> body;
    };

    struct BreakStatement : ASTNode
    {
    };

    struct ContinueStatement : ASTNode
    {
    };

    struct LiteralExpression : Expression
    {
        TokenType type;
        std::string value;
    };

    struct IdentifierExpression : Expression
    {
        std::string name;
    };

    struct BinaryExpression : Expression
    {
        std::unique_ptr<Expression> left;
        TokenType operation;
        std::unique_ptr<Expression> right;
    };

    struct UnaryExpression : Expression
    {
        TokenType operation;
        std::unique_ptr<Expression> operand;
    };

    struct GroupingExpression : Expression
    {
        std::unique_ptr<Expression> expression;
    };

    struct CallExpression : Expression
    {
        std::string name;
        std::vector<std::unique_ptr<Expression>> arguments;
    };

}
