
#ifndef LEXER_INCLUDED
#define LEXER_INCLUDED

#include <string>
#include <optional>
#include "token.h"

namespace BallLang {

struct TokenValue {
    TokenValue(Token type, std::string value): type(type), stringVal(value) {
        switch (type) {
            case Token::DEF: case Token::EXTERN: case Token::IDENTIFIER:
                break;
            default: 
                throw "ERROR";
        }
    }

    TokenValue(Token type, double value): type(type), doubleVal(value) {
        if (type != Token::NUMBER) throw "ERROR";
    }

    TokenValue(Token type): type(type) {
        if (type != Token::ENDOFFILE) throw "ERROR";
    }

    const Token type;
    const std::optional<std::string> stringVal;
    const std::optional<double> doubleVal;
};

const TokenValue getTokenValue();

}

#endif
