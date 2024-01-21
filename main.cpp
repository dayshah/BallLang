
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"
#include <iostream>

int main() {
    while (true) {
        std::cout << "> ";
        const TokenValue tokenValue = getTokenValue();
        switch(tokenValue.type) {
            case Token::ENDOFFILE:
                return;
            case Token::ENDOFLINE:
                break;
            case Token::DEF:
                //handleDefinition();
                break;
            case Token::EXTERN:
                //handleExtern();
                break;
            default:
                //handleTopLevel();
                break;
        }
    }
}

