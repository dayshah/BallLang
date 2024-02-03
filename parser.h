#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "abstract_syntax_tree.h"
#include "lexer.h"
#include <unordered_map>

namespace BallLang
{

void handleTopLevel(const Token& token);
void handleExtern(const Token& token);
void handleDefinition(const Token& token);

static const std::unordered_map<char, int> BinopPrecedence{
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40}
};

}
#endif
