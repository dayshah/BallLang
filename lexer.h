
#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED

#include <string>
#include <optional>

namespace BallLang {

enum TokenType {
    ENDOFFILE,
    ENDOFLINE,
    DEF,
    EXTERN,
    IDENTIFIER,
    NUMBER,
    OPEN_PAREN,
    CLOSE_PAREN,
    BINOP,
    COMMA,
    ERROR,
};

const std::unordered_map<char, int> BinopPrecedence{
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40}
};

struct Token {
    Token(TokenType type, const double value):
        type(type), value(value) {}
    
    Token(TokenType type, std::string&& value):
        type(type), value(std::move(value)) {}

    Token(TokenType type, const char value):
        type(type), value(value) {}

    Token(TokenType type): type(type) {} // still allocating space for variant here, could change structure

    const TokenType type;
    std::variant<std::string, double, char> value;
};

Token getTok();

}

#endif
