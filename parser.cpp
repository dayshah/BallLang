
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"
#include <iostream>
#include <optional>
#include <variant>
#include <vector>

namespace BallLang
{

ExprAST parsePrimary() {
    Token current = getTok();
    switch(current.type) {
        case IDENTIFIER:
            if (const std::string* value = std::get_if<std::string>(&current.value))
                return VariableExprAST(*value);
            else 
                throw "ERROR: No stringVal in IDENTIFIER TokenValue";
        case NUMBER:
            if (const double* value = std::get_if<double>(&current.value))
                return NumberExprAST(*value);
            else 
                throw "ERROR: No doubleVal in NUMBER TokenValue";
        case DEF:
        case EXTERN:
        case ERROR:
            throw "ERROR: TokenValue got set to error...";
        default:
            throw "bro i dont know";
    }
}

std::optional<PrototypeAST> parsePrototype(const Token& token) {
    if (token.type != TokenType::IDENTIFIER) return std::nullopt;
    const std::string& functionName = std::get<std::string>(token.value);
    const Token openParen = getTok();
    if (openParen.type != TokenType::OPEN_PAREN) return std::nullopt;

    std::vector<std::string> functionArgs{};
    while (true) {
        const Token arg = getTok();
        if (arg.type == TokenType::IDENTIFIER)
            functionArgs.emplace_back(std::move(std::get<std::string>(arg.value)));
        else if (arg.type == TokenType::CLOSE_PAREN)
            return PrototypeAST { functionName, std::move(functionArgs) };
        else
            return std::nullopt;
    }
}

std::optional<FunctionAST> parseDefinition(const Token& _token) { // throw away def
    std::optional<PrototypeAST> prototype = parsePrototype(getTok());
    if (!prototype.has_value()) return std::nullopt;
    std::optional<ExprAST> expression = parseExpression(getTok());
    if (!expression.has_value()) return std::nullopt;
    return FunctionAST {
        std::move(prototype.value()),
        std::move(expression.value())
    };
}

std::optional<FunctionAST> parseTopLevelExpr(const Token& token) {
    if (std::optional<ExprAST> expression = parseExpression(token))
        return FunctionAST {
            std::move(PrototypeAST {"anonymous_expression", std::vector<std::string>{}}),
            std::move(expression.value())
        };
    else return std::nullopt;
}

std::optional<PrototypeAST> parseExtern(const Token& _token) { // throw away initial extern
    return parsePrototype(getTok());
}

void handleTopLevel(const Token& token) { 
    if (parseTopLevelExpr(token).has_value()) std::cout << "parsed top level"; 
    else getTok();
}
void handleExtern(const Token& token) { 
    if (parseExtern(token).has_value()) std::cout << "parsed extern";
    else getTok();
}
void handleDefinition(const Token& token) { 
    if (parseDefinition(token).has_value()) std::cout << "parsed definition";
    else getTok();
}

}
