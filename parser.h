#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "abstract_syntax_tree.h"

ExprAST parsePrimary();

ExprAST parseIdentifier(const std::string& identifier);

#endif
