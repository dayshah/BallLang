#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "abstract_syntax_tree.h"
#include "lexer.h"
#include <unordered_map>
#include <iostream>
#include <optional>

namespace BallLang
{

std::optional<ExprAST> parseExpression(Token&& token);

std::optional<PrototypeAST> parseExtern(Token&& _token);
std::optional<FunctionAST> parseTopLevelExpr(Token&& token);
std::optional<FunctionAST> parseDefinition(Token&& _token);

inline void handleTopLevel(Token&& token) { 
    if (parseTopLevelExpr(std::move(token)).has_value()) std::cout << "Parsed top level" << std::endl; 
    else std::cout << "Failed to parse top level" << std::endl;
}
inline void handleExtern(Token&& token) { 
    if (parseExtern(std::move(token)).has_value()) std::cout << "Parsed extern";
    else std::cout << "Failed to parse extern" << std::endl;
}
inline void handleDefinition(Token&& token) { 
    if (parseDefinition(std::move(token)).has_value()) std::cout << "Parsed definition";
    else std::cout << "Failed to parse definition" << std::endl;
}

}
#endif
