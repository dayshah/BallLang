#ifndef PARSER_INCLUDED
#define PARSER_INCLUDED

#include "abstract_syntax_tree.h"
#include <unordered_map>

namespace BallLang
{

ExprAST parsePrimary();

static const std::unordered_map<char, int> BinopPrecedence{
    {'a', 1}
};

}
#endif
