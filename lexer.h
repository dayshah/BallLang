
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
    Token(TokenType type, const double value):
        type(type), value(value) {}
    
    Token(TokenType type, std::string&& value):
        type(type), value(std::move(value)) {}

    Token(TokenType type): type(type) {}

    const TokenType type;
    std::variant<std::string,double> value;
};

Token getTok();

}

#endif
