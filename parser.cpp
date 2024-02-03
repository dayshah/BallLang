
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"
#include <iostream>
#include <optional>
#include <variant>
#include <vector>

namespace BallLang
{

std::optional<FunctionAST> parseDefinition(Token& _token);
std::optional<PrototypeAST> parseExtern(Token& _token);

std::optional<ExprAST> parsePrimary() {
    Token current = getTok();
    switch(current.type) {
        case IDENTIFIER: {
            std::string& value = std::get<std::string>(current.value);
            return VariableExprAST(std::move(value));
        }
        case NUMBER: {
            double value = std::get<double>(current.value);
            return NumberExprAST(value);
        }
        case DEF:
            return parseDefinition(current);
        case EXTERN:
            return parseExtern(current);
        case ERROR:
            return std::nullopt;
        default:
            return std::nullopt;
    }
}

std::optional<ExprAST> parseExpression(Token token) {
    return std::nullopt;
}

// funcName ( args... )
std::optional<PrototypeAST> parsePrototype(Token token) {
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
std::optional<FunctionAST> parseDefinition(Token& _token) { // throw away def
    std::optional<PrototypeAST> prototype = parsePrototype(getTok());
    if (!prototype.has_value()) return std::nullopt;
    std::optional<ExprAST> expression = parseExpression(getTok());
    if (!expression.has_value()) return std::nullopt;
    return FunctionAST {
        std::move(prototype.value()),
        std::move(expression.value())
    };
}

// expression {functionAST}
std::optional<FunctionAST> parseTopLevelExpr(Token& token) {
    if (std::optional<ExprAST> expression = parseExpression(token))
        return FunctionAST {
            std::move(PrototypeAST {"anonymous_expression", std::vector<std::string>{}}),
            std::move(expression.value())
        };
    else return std::nullopt;
}

// extern {prototypeAST}
std::optional<PrototypeAST> parseExtern(Token& _token) { // throw away initial extern
    return parsePrototype(getTok());
}

void handleTopLevel(Token& token) { 
    if (parseTopLevelExpr(token).has_value()) std::cout << "parsed top level"; 
    else getTok();
}
void handleExtern(Token& token) { 
    if (parseExtern(token).has_value()) std::cout << "parsed extern";
    else getTok();
}
void handleDefinition(Token& token) { 
    if (parseDefinition(token).has_value()) std::cout << "parsed definition";
    else getTok();
}

}
