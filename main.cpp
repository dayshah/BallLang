
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"
#include <iostream>
#include <version>

namespace BallLang
{
int main() {
    std::cout << "The version of C++ that clang is using is: " << __cplusplus << std::endl;
    while (true) {
        std::cout << "> ";
        const TokenValue tokenValue = getTokenValue();
        switch(tokenValue.type) {
            case Token::ENDOFFILE:
                return 0;
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
}
