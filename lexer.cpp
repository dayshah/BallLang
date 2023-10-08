
#include <iostream>
#include <unordered_map>
#include "token.h"

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
        if (type != EOF) throw "ERROR";
    }

    const Token type;
    const std::optional<std::string> stringVal;
    const std::optional<double> doubleVal;
};

TokenValue getTokenValue() {

    char c = getchar();
    while (c == ' ') c = getchar();

    const std::unordered_map<std::string, Token> whichToken{
        {"def", Token::DEF},
        {"extern", Token::EXTERN},
    };

    if (isalpha(c)) {
        std::string identifier{};
        do {
            identifier.push_back(c); 
            c = getchar();
        } while (isalnum(c));
        if (whichToken.find(identifier) == whichToken.end())
            return Token::IDENTIFIER;
        else
            return whichToken.at(identifier);
    }

    if (isdigit(c) || c == '.') {
        std::string number;
        do {
            number.push_back(c);
            c = getchar();
        } while (isdigit(c) || c == '.');
        double numberVal = strtod(number.c_str(), 0);
    }

    if (c == '#') {
        do {
            c = getchar();
        } while (c != EOF && c != '\n' && c != '\r');
        if (c != EOF)
            return getTokenValue();
    }

    if (c == EOF) return Token::ENDOFFILE;

    return Token::ERROR;
}






int main() {
    std::cout << "Lexing time" << "\n";
}
