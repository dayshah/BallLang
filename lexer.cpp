
#include <iostream>
#include <unordered_map>
#include "lexer.h"
#include "parser.h"

namespace BallLang
{

Token getTok() {
    char c;
    do { c = getchar(); } while (c == ' ');

    if (c == EOF)
        return Token(ENDOFFILE);
    else if (c == '(')
        return Token(OPEN_PAREN);
    else if (c == ')')
        return Token(CLOSE_PAREN);
    else if (c == ',')
        return Token(COMMA);
    else if (BinopPrecedence.find(c) != BinopPrecedence.end())
        return Token(BINOP, c);
    else if (isalpha(c)) { // an identifier
        std::string identifier{};
        do {
            identifier.push_back(c);
            c = getchar();
        } while (isalnum(c));
        if (identifier == "def") return Token(DEF);
        else if (identifier == "extern") return Token(EXTERN);
        else return Token(IDENTIFIER, std::move(identifier));
    }
    else if (isdigit(c) || c == '.') { // a number
        std::string number{};
        do {
            number.push_back(c);
            c = getchar();
        } while (isdigit(c) || c == '.');
        double numberVal = strtod(number.c_str(), 0);
        return Token(NUMBER, numberVal);
    }
    else if (c == '#') { // a comment
        do {
            c = getchar();
        } while (c != EOF && c != '\n' && c != '\r');
        if (c == EOF) return Token(ENDOFFILE);
        else return getTok();
    }
    else return Token(ERROR);
}

}
