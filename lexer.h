
#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED

#include <string>
#include <optional>

namespace BallLang {

enum Token {
    ENDOFFILE,
    ENDOFLINE,
    DEF,
    EXTERN,
    IDENTIFIER,
    NUMBER,
    ERROR,
};

struct TokenValue {
    TokenValue(Token type, const std::variant<std::string,double>& value): 
        type(type), value(value) {}

    TokenValue(Token type) : type(type) {}

    const Token type;
    const std::variant<std::string,double> value;
};

const TokenValue getTok();

}

#endif
