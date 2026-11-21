
#include "hurtip/lexer/lexer.hpp"
#include "hurtip/parser/parser.hpp"

#include <functional>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    using namespace hurtip;

    int passed = 0;
    int failed = 0;

    std::vector<std::unique_ptr<ASTNode>> parseSource(
        const std::string &source)
    {
        Lexer lexer(source);
        std::vector<Token> tokens = lexer.tokenize();

        Parser parser(tokens);
        return parser.parse();
    }

    void runTest(
        const std::string &name,
        const std::function<void()> &test)
    {
        try
        {
            test();
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

    void expect(bool condition, const std::string &message)
    {
        if (!condition)
        {
            throw std::runtime_error(message);
        }
    }

    template <typename T>
    T *expectNode(ASTNode *node, const std::string &message)
    {
        T *result = dynamic_cast<T *>(node);

        expect(result != nullptr, message);

        return result;
    }

    void testVariableDeclaration()
    {
        auto statements = parseSource(
            "create number = 10\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        expect(declaration->name == "number",
               "Incorrect variable name");

        auto *value =
            expectNode<LiteralExpression>(
                declaration->value.get(),
                "Expected literal expression");

        expect(value->type == TokenType::Number,
               "Expected number literal");

        expect(value->value == "10",
               "Incorrect literal value");
    }

    void testVariableAssignment()
    {
        auto statements = parseSource(
            "number = 20\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *assignment =
            expectNode<AssignmentStatement>(
                statements[0].get(),
                "Expected AssignmentStatement");

        expect(assignment->name == "number",
               "Incorrect assignment target");

        auto *value =
            expectNode<LiteralExpression>(
                assignment->value.get(),
                "Expected literal expression");

        expect(value->value == "20",
               "Incorrect assignment value");
    }

    void testLoadStatement()
    {
        auto statements = parseSource(
            "load \"math.hurtip\" as math\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *load =
            expectNode<LoadStatement>(
                statements[0].get(),
                "Expected LoadStatement");

        expect(load->path == "math.hurtip",
               "Incorrect module path");

        expect(load->alias == "math",
               "Incorrect module alias");
    }

    void testLoadWithoutAlias()
    {
        auto statements = parseSource(
            "load \"math.hurtip\"\n");

        auto *load =
            expectNode<LoadStatement>(
                statements[0].get(),
                "Expected LoadStatement");

        expect(load->path == "math.hurtip",
               "Incorrect module path");

        expect(load->alias.empty(),
               "Expected empty alias");
    }

    void testFunctionDeclaration()
    {
        auto statements = parseSource(
            "function sum(a, b)\n"
            "{\n"
            "    return a + b\n"
            "}\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *function =
            expectNode<FunctionDeclaration>(
                statements[0].get(),
                "Expected FunctionDeclaration");

        expect(function->name == "sum",
               "Incorrect function name");

        expect(function->parameters.size() == 2,
               "Expected two parameters");

        expect(function->parameters[0] == "a",
               "Incorrect first parameter");

        expect(function->parameters[1] == "b",
               "Incorrect second parameter");

        expect(function->body != nullptr,
               "Expected function body");

        expect(function->body->statements.size() == 1,
               "Expected one statement in function body");

        expectNode<ReturnStatement>(
            function->body->statements[0].get(),
            "Expected ReturnStatement");
    }

    void testFunctionWithoutParameters()
    {
        auto statements = parseSource(
            "function main()\n"
            "{\n"
            "    return\n"
            "}\n");

        auto *function =
            expectNode<FunctionDeclaration>(
                statements[0].get(),
                "Expected FunctionDeclaration");

        expect(function->parameters.empty(),
               "Expected no parameters");

        auto *returnStatement =
            expectNode<ReturnStatement>(
                function->body->statements[0].get(),
                "Expected ReturnStatement");

        expect(returnStatement->value == nullptr,
               "Expected return without value");
    }

    void testFunctionMultipleParameters()
    {
        auto statements = parseSource(
            "function calculate(a, b, c)\n"
            "{\n"
            "    return a + b + c\n"
            "}\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *function =
            expectNode<FunctionDeclaration>(
                statements[0].get(),
                "Expected FunctionDeclaration");

        expect(function->parameters.size() == 3,
               "Expected three parameters");

        expect(function->parameters[0] == "a",
               "Incorrect first parameter");

        expect(function->parameters[1] == "b",
               "Incorrect second parameter");

        expect(function->parameters[2] == "c",
               "Incorrect third parameter");
    }

    void testArithmeticPrecedence()
    {
        auto statements = parseSource(
            "create result = 1 + 2 * 3\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *addition =
            expectNode<BinaryExpression>(
                declaration->value.get(),
                "Expected addition expression");

        expect(addition->operation == TokenType::Plus,
               "Expected addition as root operation");

        expectNode<LiteralExpression>(
            addition->left.get(),
            "Expected literal on left side");

        auto *multiplication =
            expectNode<BinaryExpression>(
                addition->right.get(),
                "Expected multiplication on right side");

        expect(multiplication->operation == TokenType::Star,
               "Expected multiplication operation");
    }

    void testParenthesesPrecedence()
    {
        auto statements = parseSource(
            "create result = (1 + 2) * 3\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *multiplication =
            expectNode<BinaryExpression>(
                declaration->value.get(),
                "Expected multiplication expression");

        expect(multiplication->operation == TokenType::Star,
               "Expected multiplication as root operation");

        auto *grouping =
            expectNode<GroupingExpression>(
                multiplication->left.get(),
                "Expected grouped expression");

        auto *addition =
            expectNode<BinaryExpression>(
                grouping->expression.get(),
                "Expected addition inside grouping");

        expect(addition->operation == TokenType::Plus,
               "Expected addition inside parentheses");
    }

    void testLogicalPrecedence()
    {
        auto statements = parseSource(
            "create result = true or false and true\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *logicalOr =
            expectNode<BinaryExpression>(
                declaration->value.get(),
                "Expected logical OR");

        expect(logicalOr->operation == TokenType::Or,
               "Expected OR as root operation");

        auto *logicalAnd =
            expectNode<BinaryExpression>(
                logicalOr->right.get(),
                "Expected logical AND on right side");

        expect(logicalAnd->operation == TokenType::And,
               "Expected AND operation");
    }

    void testUnaryExpressions()
    {
        auto statements = parseSource(
            "create result = -10\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *unary =
            expectNode<UnaryExpression>(
                declaration->value.get(),
                "Expected UnaryExpression");

        expect(unary->operation == TokenType::Minus,
               "Expected unary minus");

        expectNode<LiteralExpression>(
            unary->operand.get(),
            "Expected literal operand");
    }

    void testLogicalNot()
    {
        auto statements = parseSource(
            "create result = not true\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *unary =
            expectNode<UnaryExpression>(
                declaration->value.get(),
                "Expected UnaryExpression");

        expect(unary->operation == TokenType::Not,
               "Expected logical NOT");
    }

    void testFunctionCall()
    {
        auto statements = parseSource(
            "view(10, 20)\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *call =
            expectNode<CallExpression>(
                statements[0].get(),
                "Expected CallExpression");

        expect(call->arguments.size() == 2,
               "Expected two arguments");

        auto *callee =
            expectNode<IdentifierExpression>(
                call->callee.get(),
                "Expected identifier as callee");

        expect(callee->name == "view",
               "Incorrect function name");
    }

    void testMemberAccess()
    {
        auto statements = parseSource(
            "math.sum(10, 20)\n");

        auto *call =
            expectNode<CallExpression>(
                statements[0].get(),
                "Expected CallExpression");

        auto *member =
            expectNode<MemberExpression>(
                call->callee.get(),
                "Expected MemberExpression");

        expect(member->member == "sum",
               "Incorrect member name");

        auto *object =
            expectNode<IdentifierExpression>(
                member->object.get(),
                "Expected identifier as member object");

        expect(object->name == "math",
               "Incorrect namespace name");

        expect(call->arguments.size() == 2,
               "Expected two arguments");
    }

    void testChainedMemberAccess()
    {
        auto statements = parseSource(
            "math.utils.calculate(10, 20)\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *call =
            expectNode<CallExpression>(
                statements[0].get(),
                "Expected CallExpression");

        expect(call->arguments.size() == 2,
               "Expected two arguments");

        auto *calculate =
            expectNode<MemberExpression>(
                call->callee.get(),
                "Expected calculate MemberExpression");

        expect(calculate->member == "calculate",
               "Incorrect calculate member");

        auto *utils =
            expectNode<MemberExpression>(
                calculate->object.get(),
                "Expected utils MemberExpression");

        expect(utils->member == "utils",
               "Incorrect utils member");

        auto *math =
            expectNode<IdentifierExpression>(
                utils->object.get(),
                "Expected math IdentifierExpression");

        expect(math->name == "math",
               "Incorrect root identifier");
    }

    void testNestedFunctionCalls()
    {
        auto statements = parseSource(
            "view(math.sum(10, 20))\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *outerCall =
            expectNode<CallExpression>(
                statements[0].get(),
                "Expected outer CallExpression");

        expect(outerCall->arguments.size() == 1,
               "Expected one outer argument");

        auto *outerCallee =
            expectNode<IdentifierExpression>(
                outerCall->callee.get(),
                "Expected outer function identifier");

        expect(outerCallee->name == "view",
               "Incorrect outer function name");

        auto *innerCall =
            expectNode<CallExpression>(
                outerCall->arguments[0].get(),
                "Expected nested CallExpression");

        expect(innerCall->arguments.size() == 2,
               "Expected two inner arguments");

        auto *innerMember =
            expectNode<MemberExpression>(
                innerCall->callee.get(),
                "Expected inner MemberExpression");

        expect(innerMember->member == "sum",
               "Incorrect inner member");

        auto *object =
            expectNode<IdentifierExpression>(
                innerMember->object.get(),
                "Expected inner object identifier");

        expect(object->name == "math",
               "Incorrect inner object name");
    }

    void testChainedFunctionCalls()
    {
        auto statements = parseSource(
            "math.getCalculator().sum(10, 20)\n");

        expect(statements.size() == 1,
               "Expected one statement");

        auto *outerCall =
            expectNode<CallExpression>(
                statements[0].get(),
                "Expected outer CallExpression");

        expect(outerCall->arguments.size() == 2,
               "Expected two arguments");

        auto *sum =
            expectNode<MemberExpression>(
                outerCall->callee.get(),
                "Expected sum MemberExpression");

        expect(sum->member == "sum",
               "Incorrect sum member");

        auto *innerCall =
            expectNode<CallExpression>(
                sum->object.get(),
                "Expected inner CallExpression");

        expect(innerCall->arguments.empty(),
               "Expected no arguments in getCalculator");

        auto *getCalculator =
            expectNode<MemberExpression>(
                innerCall->callee.get(),
                "Expected getCalculator MemberExpression");

        expect(getCalculator->member == "getCalculator",
               "Incorrect getCalculator member");

        auto *math =
            expectNode<IdentifierExpression>(
                getCalculator->object.get(),
                "Expected math IdentifierExpression");

        expect(math->name == "math",
               "Incorrect root identifier");
    }

    void testFunctionCallWithArithmeticArguments()
    {
        auto statements = parseSource(
            "create result = calculate(10 + 5, 20 * 2)\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *call =
            expectNode<CallExpression>(
                declaration->value.get(),
                "Expected CallExpression");

        expect(call->arguments.size() == 2,
               "Expected two arguments");

        auto *addition =
            expectNode<BinaryExpression>(
                call->arguments[0].get(),
                "Expected addition expression");

        expect(addition->operation == TokenType::Plus,
               "Expected addition operation");

        auto *multiplication =
            expectNode<BinaryExpression>(
                call->arguments[1].get(),
                "Expected multiplication expression");

        expect(multiplication->operation == TokenType::Star,
               "Expected multiplication operation");
    }

    void testDeeplyNestedFunctionCalls()
    {
        auto statements = parseSource(
            "view(sum(10, multiply(2, 3)))\n");

        auto *outerCall =
            expectNode<CallExpression>(
                statements[0].get(),
                "Expected outer CallExpression");

        auto *sumCall =
            expectNode<CallExpression>(
                outerCall->arguments[0].get(),
                "Expected sum CallExpression");

        auto *multiplyCall =
            expectNode<CallExpression>(
                sumCall->arguments[1].get(),
                "Expected multiply CallExpression");

        expect(outerCall->arguments.size() == 1,
               "Expected one outer argument");

        expect(sumCall->arguments.size() == 2,
               "Expected two sum arguments");

        expect(multiplyCall->arguments.size() == 2,
               "Expected two multiply arguments");
    }

    void testGroupedFunctionCall()
    {
        auto statements = parseSource(
            "create result = (math.sum)(10, 20)\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *call =
            expectNode<CallExpression>(
                declaration->value.get(),
                "Expected CallExpression");

        expect(call->arguments.size() == 2,
               "Expected two arguments");

        auto *grouping =
            expectNode<GroupingExpression>(
                call->callee.get(),
                "Expected GroupingExpression");

        auto *member =
            expectNode<MemberExpression>(
                grouping->expression.get(),
                "Expected MemberExpression");

        expect(member->member == "sum",
               "Incorrect member name");
    }

    void testGroupedObjectMemberAccess()
    {
        auto statements = parseSource(
            "create result = (math).utils.calculate(10)\n");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        auto *call =
            expectNode<CallExpression>(
                declaration->value.get(),
                "Expected CallExpression");

        auto *calculate =
            expectNode<MemberExpression>(
                call->callee.get(),
                "Expected calculate MemberExpression");

        expect(calculate->member == "calculate",
               "Incorrect calculate member");

        auto *utils =
            expectNode<MemberExpression>(
                calculate->object.get(),
                "Expected utils MemberExpression");

        expect(utils->member == "utils",
               "Incorrect utils member");

        auto *grouping =
            expectNode<GroupingExpression>(
                utils->object.get(),
                "Expected GroupingExpression");

        auto *math =
            expectNode<IdentifierExpression>(
                grouping->expression.get(),
                "Expected math IdentifierExpression");

        expect(math->name == "math",
               "Incorrect root identifier");
    }

    void testIfElseStatement()
    {
        auto statements = parseSource(
            "if (true)\n"
            "{\n"
            "    create number = 10\n"
            "}\n"
            "else\n"
            "{\n"
            "    create number = 20\n"
            "}\n");

        auto *statement =
            expectNode<IfStatement>(
                statements[0].get(),
                "Expected IfStatement");

        expect(statement->thenBranch != nullptr,
               "Expected then branch");

        expect(statement->elseBranch != nullptr,
               "Expected else branch");

        expect(statement->thenBranch->statements.size() == 1,
               "Expected one statement in then branch");

        expect(statement->elseBranch->statements.size() == 1,
               "Expected one statement in else branch");
    }

    void testWhileStatement()
    {
        auto statements = parseSource(
            "while (true)\n"
            "{\n"
            "    break\n"
            "}\n");

        auto *statement =
            expectNode<WhileStatement>(
                statements[0].get(),
                "Expected WhileStatement");

        expect(statement->body != nullptr,
               "Expected while body");

        expect(statement->body->statements.size() == 1,
               "Expected one statement in while body");

        expectNode<BreakStatement>(
            statement->body->statements[0].get(),
            "Expected BreakStatement");
    }

    void testBreakAndContinue()
    {
        auto statements = parseSource(
            "while (true)\n"
            "{\n"
            "    continue\n"
            "    break\n"
            "}\n");

        auto *loop =
            expectNode<WhileStatement>(
                statements[0].get(),
                "Expected WhileStatement");

        expect(loop->body->statements.size() == 2,
               "Expected two statements");

        expectNode<ContinueStatement>(
            loop->body->statements[0].get(),
            "Expected ContinueStatement");

        expectNode<BreakStatement>(
            loop->body->statements[1].get(),
            "Expected BreakStatement");
    }

    void testEmptyProgram()
    {
        auto statements = parseSource("");

        expect(statements.empty(),
               "Expected empty program");
    }

    void testExpectedError(
        const std::string &name,
        const std::string &source,
        const std::string &expectedMessage)
    {
        runTest(name, [&]()
                {
                    try
                    {
                        parseSource(source);
                    }
                    catch (const std::exception &error)
                    {
                        expect(
                            std::string(error.what()).find(expectedMessage) !=
                                std::string::npos,
                            "Unexpected error message: " +
                                std::string(error.what()));

                        return;
                    }

                    throw std::runtime_error(
                        "Expected parser error, but parsing succeeded"); });
    }

    // Parser input validation tests

    void testParserRejectsEmptyTokens()
    {
        const std::vector<Token> tokens;

        try
        {
            Parser parser(tokens);

            throw std::runtime_error(
                "Expected parser to reject empty tokens");
        }
        catch (const std::invalid_argument &error)
        {
            expect(
                std::string(error.what()).find("Parser received an empty token list") !=
                    std::string::npos,
                "Unexpected error message");
        }
    }

    void testParserRejectsTokensWithoutEOF()
    {
        const std::vector<Token> tokens = {
            {TokenType::Number, "10", 1, 1}};

        try
        {
            Parser parser(tokens);

            throw std::runtime_error(
                "Expected parser to reject tokens without EOF");
        }
        catch (const std::invalid_argument &error)
        {
            expect(
                std::string(error.what()).find("Parser expected an EndOfFile token") !=
                    std::string::npos,
                "Unexpected error message");
        }
    }

    void testParserAcceptsTokensWithEOF()
    {
        const std::vector<Token> tokens = {
            {TokenType::Create, "create", 1, 1},
            {TokenType::Identifier, "number", 1, 8},
            {TokenType::Equal, "=", 1, 15},
            {TokenType::Number, "10", 1, 17},
            {TokenType::NewLine, "\n", 1, 19},
            {TokenType::EndOfFile, "", 2, 1}};

        Parser parser(tokens);

        const auto statements = parser.parse();

        expect(
            statements.size() == 1,
            "Expected one parsed statement");

        auto *declaration =
            expectNode<CreateStatement>(
                statements[0].get(),
                "Expected CreateStatement");

        expect(
            declaration->name == "number",
            "Incorrect variable name");

        auto *value =
            expectNode<LiteralExpression>(
                declaration->value.get(),
                "Expected LiteralExpression");

        expect(
            value->value == "10",
            "Incorrect literal value");
    }
}
int main()
{
    std::cout << "Running Hurtip Parser tests...\n\n";

    runTest("variable declaration", testVariableDeclaration);
    runTest("variable assignment", testVariableAssignment);
    runTest("load statement", testLoadStatement);
    runTest("load without alias", testLoadWithoutAlias);

    runTest("function declaration", testFunctionDeclaration);
    runTest("function without parameters", testFunctionWithoutParameters);
    runTest("function with multiple parameters", testFunctionMultipleParameters);

    runTest("arithmetic precedence", testArithmeticPrecedence);
    runTest("parentheses precedence", testParenthesesPrecedence);
    runTest("logical precedence", testLogicalPrecedence);
    runTest("unary expressions", testUnaryExpressions);
    runTest("logical NOT", testLogicalNot);

    runTest("function call", testFunctionCall);
    runTest("member access", testMemberAccess);
    runTest("chained member access", testChainedMemberAccess);
    runTest("nested function calls", testNestedFunctionCalls);
    runTest("chained function calls", testChainedFunctionCalls);

    runTest(
        "function call with arithmetic arguments",
        testFunctionCallWithArithmeticArguments);

    runTest(
        "deeply nested function calls",
        testDeeplyNestedFunctionCalls);

    runTest(
        "grouped function call",
        testGroupedFunctionCall);

    runTest(
        "grouped object member access",
        testGroupedObjectMemberAccess);

    runTest("if and else statement", testIfElseStatement);
    runTest("while statement", testWhileStatement);
    runTest("break and continue", testBreakAndContinue);

    runTest("empty program", testEmptyProgram);

    // Parser error tests

    testExpectedError(
        "return outside function",
        "return 10\n",
        "'return' can only be used inside a function");

    testExpectedError(
        "break outside loop",
        "break\n",
        "'break' can only be used inside a loop");

    testExpectedError(
        "continue outside loop",
        "continue\n",
        "'continue' can only be used inside a loop");

    testExpectedError(
        "trailing function parameter comma",
        "function sum(a,)\n{\nreturn a\n}\n",
        "Expected a parameter name after ','");

    testExpectedError(
        "invalid function parameter type",
        "function sum(a, 10)\n{\nreturn a\n}\n",
        "Expected a parameter name after ','");

    testExpectedError(
        "missing expression",
        "create number =\n",
        "Expected an expression");

    testExpectedError(
        "missing function parenthesis",
        "function sum(a, b\n{\nreturn a\n}\n",
        "Expected ')' after function parameters");

    testExpectedError(
        "invalid member access",
        "math.\n",
        "Expected a member name after '.'");

    testExpectedError(
        "incomplete arithmetic argument",
        "create result = calculate(10 + )\n",
        "Expected an expression");

    testExpectedError(
        "missing grouped expression parenthesis",
        "create result = ((10 + 20)\n",
        "Expected ')' after expression");

    testExpectedError(
        "missing function call parenthesis",
        "create result = calculate(10, 20\n",
        "Expected ')' after function arguments");

    testExpectedError(
        "invalid member access inside grouping",
        "create result = (math.)\n",
        "Expected a member name after '.'");

    // Parser input validation tests

    runTest(
        "parser rejects empty tokens",
        testParserRejectsEmptyTokens);

    runTest(
        "parser rejects tokens without EOF",
        testParserRejectsTokensWithoutEOF);

    runTest(
        "parser accepts tokens with EOF",
        testParserAcceptsTokensWithEOF);

    std::cout << "\n-----------------------------\n";
    std::cout << "Passed: " << passed << '\n';
    std::cout << "Failed: " << failed << '\n';
    std::cout << "-----------------------------\n";

    return failed == 0 ? 0 : 1;
}
