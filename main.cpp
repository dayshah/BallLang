
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
        Token token = getTok();
        switch(token.type) {
            case TokenType::ENDOFFILE:
                return 0;
            case TokenType::ENDOFLINE:
                break;
            case TokenType::DEF:
                handleDefinition(std::move(token));
                break;
            case TokenType::EXTERN:
                handleExtern(std::move(token));
                break;
            default:
                handleTopLevel(std::move(token));
                break;
        }
    }
}

}
