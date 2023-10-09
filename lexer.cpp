
#include <iostream>
#include <unordered_map>
#include "lexer.h"

const TokenValue getTokenValue() {
    char c = getchar();
    while (c == ' ') c = getchar();

    if (isalpha(c)) {
        std::string identifier;
        const std::unordered_map<std::string, Token> whichToken{
            {"def", Token::DEF},
            {"extern", Token::EXTERN},
        };
        do {
            identifier.push_back(c); 
            c = getchar();
        } while (isalnum(c));
        if (whichToken.find(identifier) == whichToken.end())
            return TokenValue(Token::IDENTIFIER, identifier);
        else 
            return TokenValue(whichToken.at(identifier), identifier);
   }

    if (isdigit(c) || c == '.') {
        std::string number;
        do {
            number.push_back(c);
            c = getchar();
        } while (isdigit(c) || c == '.');
        double numberVal = strtod(number.c_str(), 0);
        return TokenValue(Token::NUMBER, numberVal);
    }

    if (c == '#') {
        do {
            c = getchar();
        } while (c != EOF && c != '\n' && c != '\r');
        if (c != EOF)
            return getTokenValue();
    }

    if (c == EOF) return TokenValue(Token::ENDOFFILE);

    return TokenValue(Token::ERROR);
}

int main() {
    std::cout << "Lex Luthor" << "\n";
        
}
