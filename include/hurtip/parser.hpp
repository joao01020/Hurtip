
#pragma once

#include "hurtip/ast.hpp"

#include <cstddef>
#include <memory>
#include <vector>

namespace hurtip
{

    class Parser
    {
    public:
        explicit Parser(const std::vector<Token> &tokens);

        std::vector<std::unique_ptr<ASTNode>> parse();

    private:
        const std::vector<Token> &tokens;
        std::size_t position = 0;

        int loopDepth = 0;

        const Token &currentToken() const;
        const Token &advance();

        bool match(TokenType type);
        bool check(TokenType type) const;

        std::unique_ptr<ASTNode> parseStatement();

        std::unique_ptr<CreateStatement> parseCreateStatement();
        std::unique_ptr<AssignmentStatement> parseAssignmentStatement();

        std::unique_ptr<IfStatement> parseIfStatement();
        std::unique_ptr<WhileStatement> parseWhileStatement();

        std::unique_ptr<BreakStatement> parseBreakStatement();
        std::unique_ptr<ContinueStatement> parseContinueStatement();

        std::unique_ptr<BlockStatement> parseBlockStatement();

        // Expression parsing
        std::unique_ptr<Expression> parseExpression();

        // Logical expressions
        std::unique_ptr<Expression> parseOrExpression();
        std::unique_ptr<Expression> parseAndExpression();
        std::unique_ptr<Expression> parseNotExpression();

        // Comparison expressions
        std::unique_ptr<Expression> parseEqualityExpression();
        std::unique_ptr<Expression> parseComparisonExpression();

        // Arithmetic expressions
        std::unique_ptr<Expression> parseAdditiveExpression();
        std::unique_ptr<Expression> parseMultiplicativeExpression();
        std::unique_ptr<Expression> parseUnaryExpression();

        // Primary expressions
        std::unique_ptr<Expression> parsePrimaryExpression();

        std::unique_ptr<CallExpression> parseCallExpression();
    };

}
