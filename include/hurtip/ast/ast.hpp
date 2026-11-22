
#pragma once

#include "hurtip/token.hpp"

#include <memory>
#include <string>
#include <vector>

namespace hurtip
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

    // Statements

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

    struct LoadStatement : ASTNode
    {
        std::string path;
        std::string alias;
    };

    struct ImportStatement : ASTNode
    {
        std::string name;
        std::string alias;
    };

    struct BlockStatement : ASTNode
    {
        std::vector<std::unique_ptr<ASTNode>> statements;
    };

    struct FunctionDeclaration : ASTNode
    {
        std::string name;
        std::vector<std::string> parameters;
        std::unique_ptr<BlockStatement> body;
    };

    struct ReturnStatement : ASTNode
    {
        std::unique_ptr<Expression> value;
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

    // Expressions

    struct LiteralExpression : Expression
    {
        TokenType type;
        std::string value;
    };

    struct IdentifierExpression : Expression
    {
        std::string name;
    };

    struct MemberExpression : Expression
    {
        std::unique_ptr<Expression> object;
        std::string member;
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

    // Array expression

    struct ArrayExpression : Expression
    {
        std::vector<std::unique_ptr<Expression>> elements;
    };

    // Array index expression

    struct IndexExpression : Expression
    {
        std::unique_ptr<Expression> object;
        std::unique_ptr<Expression> index;
    };

    struct CallExpression : Expression
    {
        std::unique_ptr<Expression> callee;
        std::vector<std::unique_ptr<Expression>> arguments;
    };

}
