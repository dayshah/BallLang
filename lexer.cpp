
#include <iostream>
#include <unordered_map>
#include "lexer.h"

namespace BallLang
{

const std::unordered_map<std::string, Token> whichToken{
    {"def", Token::DEF},
    {"extern", Token::EXTERN},
};

const TokenValue getTok() {
    char c = getchar();
    while (c == ' ') c = getchar();

    if (isalpha(c)) {
        std::string identifier{};
        do {
            identifier.push_back(c);
            c = getchar();
        } while (isalnum(c));
        const auto& token_p = whichToken.find(identifier);
        return token_p == whichToken.end() ?
            TokenValue(Token::IDENTIFIER, identifier) :
            TokenValue(token_p->second, identifier);
    }
    else if (isdigit(c) || c == '.') {
        std::string number{};
        do {
            number.push_back(c);
            c = getchar();
        } while (isdigit(c) || c == '.');
        double numberVal = strtod(number.c_str(), 0);
        return TokenValue(Token::NUMBER, numberVal);
    }
    else if (c == '#') {
        do {
            c = getchar();
        } while (c != EOF && c != '\n' && c != '\r');
        if (c == EOF) return TokenValue(Token::ENDOFFILE);
        else return getTok();
    }
    else if (c == EOF) return TokenValue(Token::ENDOFFILE);
    else return TokenValue(Token::ERROR);
}

}
