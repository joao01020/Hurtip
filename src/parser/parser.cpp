
#include "hurtip/parser/parser.hpp"

#include <stdexcept>
#include <string>
#include <utility>

namespace hurtip
{

    static std::runtime_error parserError(
        const Token &token,
        const std::string &message)
    {
        return std::runtime_error(
            "Line " + std::to_string(token.line) +
            ", column " + std::to_string(token.column) +
            ": " + message);
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

    // Program parsing

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

    // Statement parsing

    std::unique_ptr<ASTNode> Parser::parseStatement()
    {
        if (check(TokenType::Create))
        {
            return parseCreateStatement();
        }

        if (check(TokenType::Load))
        {
            return parseLoadStatement();
        }

        if (check(TokenType::Function))
        {
            return parseFunctionDeclaration();
        }

        if (check(TokenType::Return))
        {
            return parseReturnStatement();
        }

        if (check(TokenType::If))
        {
            return parseIfStatement();
        }

        if (check(TokenType::While))
        {
            return parseWhileStatement();
        }

        if (check(TokenType::Break))
        {
            return parseBreakStatement();
        }

        if (check(TokenType::Continue))
        {
            return parseContinueStatement();
        }

        if (check(TokenType::Identifier))
        {
            if (position + 1 < tokens.size() &&
                tokens[position + 1].type == TokenType::Equal)
            {
                return parseAssignmentStatement();
            }

            return parseExpression();
        }

        throw parserError(
            currentToken(),
            "Unexpected token: " + currentToken().lexeme);
    }

    // Variable declaration

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

    // Load statement

    std::unique_ptr<LoadStatement> Parser::parseLoadStatement()
    {
        const Token &loadToken = advance();

        if (!check(TokenType::String))
        {
            throw parserError(
                currentToken(),
                "Expected a file path after 'load'");
        }

        auto statement = std::make_unique<LoadStatement>();

        statement->line = loadToken.line;
        statement->path = advance().lexeme;

        if (match(TokenType::As))
        {
            if (!check(TokenType::Identifier))
            {
                throw parserError(
                    currentToken(),
                    "Expected a module name after 'as'");
            }

            statement->alias = advance().lexeme;
        }

        return statement;
    }

    // Variable assignment

    std::unique_ptr<AssignmentStatement>
    Parser::parseAssignmentStatement()
    {
        const Token &nameToken = advance();

        auto statement = std::make_unique<AssignmentStatement>();

        statement->line = nameToken.line;
        statement->name = nameToken.lexeme;

        if (!match(TokenType::Equal))
        {
            throw parserError(
                currentToken(),
                "Expected '=' after variable name");
        }

        statement->value = parseExpression();

        return statement;
    }

    // Function declaration

    std::unique_ptr<FunctionDeclaration>
    Parser::parseFunctionDeclaration()
    {
        const Token &functionToken = advance();

        if (!check(TokenType::Identifier))
        {
            throw parserError(
                currentToken(),
                "Expected a function name after 'function'");
        }

        auto statement = std::make_unique<FunctionDeclaration>();

        statement->line = functionToken.line;
        statement->name = advance().lexeme;

        if (!match(TokenType::LeftParen))
        {
            throw parserError(
                currentToken(),
                "Expected '(' after function name");
        }

        // Function parameters

        if (!check(TokenType::RightParen))
        {
            if (!check(TokenType::Identifier))
            {
                throw parserError(
                    currentToken(),
                    "Expected a parameter name");
            }

            statement->parameters.push_back(advance().lexeme);

            while (match(TokenType::Comma))
            {
                if (!check(TokenType::Identifier))
                {
                    throw parserError(
                        currentToken(),
                        "Expected a parameter name after ','");
                }

                statement->parameters.push_back(
                    advance().lexeme);
            }
        }

        if (!match(TokenType::RightParen))
        {
            throw parserError(
                currentToken(),
                "Expected ')' after function parameters");
        }

        // Allow new lines before the function body.

        while (match(TokenType::NewLine))
        {
        }

        // A function has its own loop context.
        // A break or continue cannot escape into an outer loop.

        const int previousLoopDepth = loopDepth;

        loopDepth = 0;
        functionDepth++;

        try
        {
            statement->body = parseBlockStatement();
        }
        catch (...)
        {
            functionDepth--;
            loopDepth = previousLoopDepth;
            throw;
        }

        functionDepth--;
        loopDepth = previousLoopDepth;

        return statement;
    }

    // Return statement

    std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
    {
        const Token &returnToken = advance();

        if (functionDepth <= 0)
        {
            throw parserError(
                returnToken,
                "'return' can only be used inside a function");
        }

        auto statement = std::make_unique<ReturnStatement>();

        statement->line = returnToken.line;

        // Return may have a value or be used without one.

        if (!check(TokenType::NewLine) &&
            !check(TokenType::RightBrace) &&
            !check(TokenType::EndOfFile))
        {
            statement->value = parseExpression();
        }

        return statement;
    }

    // If and else statements

    std::unique_ptr<IfStatement> Parser::parseIfStatement()
    {
        const Token &ifToken = advance();

        auto statement = std::make_unique<IfStatement>();
        statement->line = ifToken.line;

        if (!match(TokenType::LeftParen))
        {
            throw parserError(
                currentToken(),
                "Expected '(' after 'if'");
        }

        statement->condition = parseExpression();

        if (!match(TokenType::RightParen))
        {
            throw parserError(
                currentToken(),
                "Expected ')' after if condition");
        }

        statement->thenBranch = parseBlockStatement();

        const std::size_t afterThenBranch = position;

        while (match(TokenType::NewLine))
        {
        }

        if (match(TokenType::Else))
        {
            statement->elseBranch = parseBlockStatement();
        }
        else
        {
            position = afterThenBranch;
        }

        return statement;
    }

    // While statement

    std::unique_ptr<WhileStatement> Parser::parseWhileStatement()
    {
        const Token &whileToken = advance();

        auto statement = std::make_unique<WhileStatement>();
        statement->line = whileToken.line;

        if (!match(TokenType::LeftParen))
        {
            throw parserError(
                currentToken(),
                "Expected '(' after 'while'");
        }

        statement->condition = parseExpression();

        if (!match(TokenType::RightParen))
        {
            throw parserError(
                currentToken(),
                "Expected ')' after while condition");
        }

        loopDepth++;

        try
        {
            statement->body = parseBlockStatement();
        }
        catch (...)
        {
            loopDepth--;
            throw;
        }

        loopDepth--;

        return statement;
    }

    // Break statement

    std::unique_ptr<BreakStatement> Parser::parseBreakStatement()
    {
        const Token &breakToken = advance();

        if (loopDepth <= 0)
        {
            throw parserError(
                breakToken,
                "'break' can only be used inside a loop");
        }

        auto statement = std::make_unique<BreakStatement>();

        statement->line = breakToken.line;

        return statement;
    }

    // Continue statement

    std::unique_ptr<ContinueStatement> Parser::parseContinueStatement()
    {
        const Token &continueToken = advance();

        if (loopDepth <= 0)
        {
            throw parserError(
                continueToken,
                "'continue' can only be used inside a loop");
        }

        auto statement = std::make_unique<ContinueStatement>();

        statement->line = continueToken.line;

        return statement;
    }

    // Block parsing

    std::unique_ptr<BlockStatement> Parser::parseBlockStatement()
    {
        if (!match(TokenType::LeftBrace))
        {
            throw parserError(
                currentToken(),
                "Expected '{' to begin block");
        }

        auto block = std::make_unique<BlockStatement>();
        block->line = tokens[position - 1].line;

        while (!check(TokenType::RightBrace) &&
               !check(TokenType::EndOfFile))
        {
            if (match(TokenType::NewLine))
            {
                continue;
            }

            block->statements.push_back(parseStatement());

            if (!check(TokenType::NewLine) &&
                !check(TokenType::RightBrace))
            {
                throw parserError(
                    currentToken(),
                    "Expected a new line or '}' after statement");
            }
        }

        if (!match(TokenType::RightBrace))
        {
            throw parserError(
                currentToken(),
                "Expected '}' to close block");
        }

        return block;
    }

    // Expression parsing

    std::unique_ptr<Expression> Parser::parseExpression()
    {
        return parseOrExpression();
    }

    // Logical OR

    std::unique_ptr<Expression> Parser::parseOrExpression()
    {
        auto expression = parseAndExpression();

        while (check(TokenType::Or))
        {
            const Token &operation = advance();

            auto binary = std::make_unique<BinaryExpression>();

            binary->line = operation.line;
            binary->operation = operation.type;
            binary->left = std::move(expression);
            binary->right = parseAndExpression();

            expression = std::move(binary);
        }

        return expression;
    }

    // Logical AND

    std::unique_ptr<Expression> Parser::parseAndExpression()
    {
        auto expression = parseNotExpression();

        while (check(TokenType::And))
        {
            const Token &operation = advance();

            auto binary = std::make_unique<BinaryExpression>();

            binary->line = operation.line;
            binary->operation = operation.type;
            binary->left = std::move(expression);
            binary->right = parseNotExpression();

            expression = std::move(binary);
        }

        return expression;
    }

    // Logical NOT

    std::unique_ptr<Expression> Parser::parseNotExpression()
    {
        if (check(TokenType::Not))
        {
            const Token &operation = advance();

            auto unary = std::make_unique<UnaryExpression>();

            unary->line = operation.line;
            unary->operation = operation.type;
            unary->operand = parseNotExpression();

            return unary;
        }

        return parseEqualityExpression();
    }

    // Equality comparisons

    std::unique_ptr<Expression> Parser::parseEqualityExpression()
    {
        auto expression = parseComparisonExpression();

        while (check(TokenType::EqualEqual) ||
               check(TokenType::BangEqual))
        {
            const Token &operation = advance();

            auto binary = std::make_unique<BinaryExpression>();

            binary->line = operation.line;
            binary->operation = operation.type;
            binary->left = std::move(expression);
            binary->right = parseComparisonExpression();

            expression = std::move(binary);
        }

        return expression;
    }

    // Relational comparisons

    std::unique_ptr<Expression> Parser::parseComparisonExpression()
    {
        auto expression = parseAdditiveExpression();

        while (check(TokenType::Greater) ||
               check(TokenType::Less) ||
               check(TokenType::GreaterEqual) ||
               check(TokenType::LessEqual))
        {
            const Token &operation = advance();

            auto binary = std::make_unique<BinaryExpression>();

            binary->line = operation.line;
            binary->operation = operation.type;
            binary->left = std::move(expression);
            binary->right = parseAdditiveExpression();

            expression = std::move(binary);
        }

        return expression;
    }

    // Addition and subtraction

    std::unique_ptr<Expression> Parser::parseAdditiveExpression()
    {
        auto expression = parseMultiplicativeExpression();

        while (check(TokenType::Plus) ||
               check(TokenType::Minus))
        {
            const Token &operation = advance();

            auto binary = std::make_unique<BinaryExpression>();

            binary->line = operation.line;
            binary->operation = operation.type;
            binary->left = std::move(expression);
            binary->right = parseMultiplicativeExpression();

            expression = std::move(binary);
        }

        return expression;
    }

    // Multiplication and division

    std::unique_ptr<Expression> Parser::parseMultiplicativeExpression()
    {
        auto expression = parseUnaryExpression();

        while (check(TokenType::Star) ||
               check(TokenType::Slash))
        {
            const Token &operation = advance();

            auto binary = std::make_unique<BinaryExpression>();

            binary->line = operation.line;
            binary->operation = operation.type;
            binary->left = std::move(expression);
            binary->right = parseUnaryExpression();

            expression = std::move(binary);
        }

        return expression;
    }

    // Numeric unary operations

    std::unique_ptr<Expression> Parser::parseUnaryExpression()
    {
        if (check(TokenType::Minus) ||
            check(TokenType::Plus))
        {
            const Token &operation = advance();

            auto unary = std::make_unique<UnaryExpression>();

            unary->line = operation.line;
            unary->operation = operation.type;
            unary->operand = parseUnaryExpression();

            return unary;
        }

        return parsePrimaryExpression();
    }

    // Primary and postfix expressions

    std::unique_ptr<Expression> Parser::parsePrimaryExpression()
    {
        std::unique_ptr<Expression> expression;

        // Literal values

        if (check(TokenType::Number) ||
            check(TokenType::String) ||
            check(TokenType::True) ||
            check(TokenType::False))
        {
            const Token &token = advance();

            auto literal = std::make_unique<LiteralExpression>();

            literal->line = token.line;
            literal->type = token.type;
            literal->value = token.lexeme;

            expression = std::move(literal);
        }

        // Identifier

        else if (check(TokenType::Identifier))
        {
            const Token &token = advance();

            auto identifier =
                std::make_unique<IdentifierExpression>();

            identifier->line = token.line;
            identifier->name = token.lexeme;

            expression = std::move(identifier);
        }

        // Grouped expression

        else if (match(TokenType::LeftParen))
        {
            auto grouping = std::make_unique<GroupingExpression>();

            grouping->expression = parseExpression();
            grouping->line = grouping->expression->line;

            if (!match(TokenType::RightParen))
            {
                throw parserError(
                    currentToken(),
                    "Expected ')' after expression");
            }

            expression = std::move(grouping);
        }

        else
        {
            throw parserError(
                currentToken(),
                "Expected an expression, got: " +
                    currentToken().lexeme);
        }

        // Postfix expressions:
        // member access and function calls

        while (true)
        {
            // Member access: object.member

            if (match(TokenType::Dot))
            {
                if (!check(TokenType::Identifier))
                {
                    throw parserError(
                        currentToken(),
                        "Expected a member name after '.'");
                }

                const Token &memberToken = advance();

                auto member = std::make_unique<MemberExpression>();

                member->line = memberToken.line;
                member->object = std::move(expression);
                member->member = memberToken.lexeme;

                expression = std::move(member);

                continue;
            }

            // Function call: expression(arguments)

            if (check(TokenType::LeftParen))
            {
                expression = parseCallExpression(
                    std::move(expression));

                continue;
            }

            break;
        }

        return expression;
    }

    // Function calls

    std::unique_ptr<CallExpression> Parser::parseCallExpression(
        std::unique_ptr<Expression> callee)
    {
        auto expression = std::make_unique<CallExpression>();

        expression->line = callee->line;
        expression->callee = std::move(callee);

        if (!match(TokenType::LeftParen))
        {
            throw parserError(
                currentToken(),
                "Expected '(' after function expression");
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
