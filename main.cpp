
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
        const Token token = getTok();
        switch(token.type) {
            case TokenType::ENDOFFILE:
                return 0;
            case TokenType::ENDOFLINE:
                break;
            case TokenType::DEF:
                handleDefinition(token);
                break;
            case TokenType::EXTERN:
                handleExtern(token);
                break;
            default:
                handleTopLevel(token);
                break;
        }
    }
}

}
