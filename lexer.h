
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
    ERROR,
};

struct Token {
    Token(TokenType type, const std::variant<std::string,double>& value): 
        type(type), value(value) {}

    Token(TokenType type) : type(type) {}

    const TokenType type;
    const std::variant<std::string,double> value;
};

const Token getTok();

}

#endif
