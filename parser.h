#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "abstract_syntax_tree.h"

ExprAST parsePrimary();

NumberExprAST parseNumber(double num);

ExprAST parseIdentifier(const std::string& identifier);

#endif
