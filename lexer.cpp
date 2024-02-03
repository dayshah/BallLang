
#include <iostream>
#include <unordered_map>
#include "lexer.h"

namespace BallLang
{

const std::unordered_map<std::string, TokenType> whichToken{
    {"def", TokenType::DEF},
    {"extern", TokenType::EXTERN},
};

const Token getTok() {
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
            Token{TokenType::IDENTIFIER, identifier} :
            Token{token_p->second, identifier};
    }
    else if (isdigit(c) || c == '.') {
        std::string number{};
        do {
            number.push_back(c);
            c = getchar();
        } while (isdigit(c) || c == '.');
        double numberVal = strtod(number.c_str(), 0);
        return Token(TokenType::NUMBER, numberVal);
    }
    else if (c == '#') {
        do {
            c = getchar();
        } while (c != EOF && c != '\n' && c != '\r');
        if (c == EOF) return Token(TokenType::ENDOFFILE);
        else return getTok();
    }
    else if (c == EOF) return Token(TokenType::ENDOFFILE);
    else return Token(TokenType::ERROR);
}

}
