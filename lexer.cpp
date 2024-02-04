
#include <iostream>
#include <unordered_map>
#include "lexer.h"
#include "parser.h"

namespace BallLang
{

const std::unordered_map<std::string, TokenType> defOrExtern{
    {"def", TokenType::DEF},
    {"extern", TokenType::EXTERN},
};

Token getTok() {
    char c;
    do { c = getchar(); } while (c == ' ');

    if (c == EOF)
        return Token(TokenType::ENDOFFILE);
    else if (c == '(')
        return Token(TokenType::OPEN_PAREN);
    else if (c == ')')
        return Token(TokenType::CLOSE_PAREN);
    else if (c == ',')
        return Token(TokenType::COMMA);
    else if (BinopPrecedence.find(c) != BinopPrecedence.end())
        return Token(TokenType::BINOP, c);
    else if (isalpha(c)) { // an identifier
        std::string identifier{};
        do {
            identifier.push_back(c);
            c = getchar();
        } while (isalnum(c));
        const auto& token_p = defOrExtern.find(identifier);
        return token_p == defOrExtern.end() ?
            Token{TokenType::IDENTIFIER, std::move(identifier)} :
            Token{token_p->second};
    }
    else if (isdigit(c) || c == '.') { // a number
        std::string number{};
        do {
            number.push_back(c);
            c = getchar();
        } while (isdigit(c) || c == '.');
        double numberVal = strtod(number.c_str(), 0);
        return Token(TokenType::NUMBER, numberVal);
    }
    else if (c == '#') { // a comment
        do {
            c = getchar();
        } while (c != EOF && c != '\n' && c != '\r');
        if (c == EOF) return Token(TokenType::ENDOFFILE);
        else return getTok();
    }
    else return Token(TokenType::ERROR);
}

}
