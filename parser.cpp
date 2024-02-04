
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"
#include <iostream>
#include <optional>
#include <variant>
#include <vector>

namespace BallLang
{

// forward declarations
std::optional<FunctionAST> parseDefinition(Token&& _token);
std::optional<PrototypeAST> parseExtern(Token&& _token);
std::optional<ExprAST> parseExpression(Token&& token);
std::optional<ExprAST> parsePrimary(Token&& token);

// variable
// identifier ( {ExprAST},... )
std::optional<ExprAST> parseIdentifierExpr(Token&& token) {
    std::string& name = std::get<std::string>(token.value);
    if (std::cin.peek() != '(') return VariableExprAST{std::move(name)};
    if (getTok().type != OPEN_PAREN) return std::nullopt; // peek didn't work
    std::vector<ExprAST> args{};
    while (std::optional<ExprAST> exprOptional = parseExpression(getTok())) {
        args.emplace_back(std::move(exprOptional.value()));
        switch(getTok().type) {
            case COMMA: continue;
            case CLOSE_PAREN: return CallExprAST {std::move(name), std::move(args)};
            default: return std::nullopt;
        }
    }
    return std::nullopt;
}

std::optional<ExprAST> parsePrimary(Token&& token) {
    switch(token.type) {
        case IDENTIFIER:
            return parseIdentifierExpr(std::move(token));
        case NUMBER:
            return NumberExprAST(std::get<double>(token.value));
        case OPEN_PAREN: {
            std::optional<ExprAST> expression = parseExpression(getTok());
            if (expression.has_value() && getTok().type == CLOSE_PAREN) 
                return expression; // hopefully rvo, if not could optimize
            else return std::nullopt;
        }
        default:
            return std::nullopt;
    }
}

// LHS {binop} RHS
std::optional<ExprAST> parseRHS(int lastPrecedence, ExprAST&& LHS) {
    Token binop = getTok();
    if (binop.type != BINOP) return std::nullopt;
    Token rhsToken = getTok();
    std::optional<ExprAST> RHS = parsePrimary(std::move(rhsToken));
    if (!RHS.has_value()) return std::nullopt;
    // need binop precedence logic
    return BinaryExprAST { 
        std::get<char>(binop.value),
        std::move(LHS), 
        std::move(RHS.value())
    };
}

// {primary} {RHS}
std::optional<ExprAST> parseExpression(Token&& token) {
    std::optional<ExprAST> LHS = parsePrimary(std::move(token));
    if (!LHS.has_value()) return std::nullopt;
    return parseRHS(0, std::move(LHS.value()));
}

// funcName ( args... )
std::optional<PrototypeAST> parsePrototype(Token&& token) {
    if (token.type != TokenType::IDENTIFIER) return std::nullopt;
    std::string& functionName = std::get<std::string>(token.value);
    const Token openParen = getTok();
    if (openParen.type != TokenType::OPEN_PAREN) return std::nullopt;

    std::vector<std::string> functionArgs{};
    while (true) {
        Token arg = getTok();
        if (arg.type == TokenType::IDENTIFIER)
            functionArgs.emplace_back(std::move(std::get<std::string>(arg.value)));
        else if (arg.type == TokenType::CLOSE_PAREN)
            return PrototypeAST { std::move(functionName), std::move(functionArgs) };
        else
            return std::nullopt;
    }
}

// def {prototype} {expression}
std::optional<FunctionAST> parseDefinition(Token&& _token) { // throw away def
    std::optional<PrototypeAST> prototype = parsePrototype(getTok());
    if (!prototype.has_value()) return std::nullopt;
    std::optional<ExprAST> expression = parseExpression(getTok());
    if (!expression.has_value()) return std::nullopt;
    return FunctionAST {
        std::move(prototype.value()),
        std::move(expression.value())
    };
}

// {expression}
std::optional<FunctionAST> parseTopLevelExpr(Token&& token) {
    if (std::optional<ExprAST> expression = parseExpression(std::move(token)))
        return FunctionAST {
            std::move(PrototypeAST {"anonymous_expression", std::vector<std::string>{}}),
            std::move(expression.value())
        };
    else return std::nullopt;
}

// extern {prototypeAST}
std::optional<PrototypeAST> parseExtern(Token&& _token) { // throw away initial extern
    return parsePrototype(getTok());
}

}
