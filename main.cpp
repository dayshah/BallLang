
#include "lexer.h"
#include "parser.h"
#include <iostream>
#include <version>
#include "llvm/Config/abi-breaking.h"

// TODO: fix to build correctly eventually
int llvm::DisableABIBreakingChecks = 1;

int main() {
    std::cout << "The version of C++ that clang is using is: " << __cplusplus << std::endl;
    while (true) {
        std::cout << "> ";
        BallLang::Token token = BallLang::getTok();
        switch(token.type) {
            case BallLang::TokenType::ENDOFFILE:
                return 0;
            case BallLang::TokenType::ENDOFLINE:
                break;
            case BallLang::TokenType::DEF:
                handleDefinition(std::move(token));
                break;
            case BallLang::TokenType::EXTERN:
                handleExtern(std::move(token));
                break;
            default:
                handleTopLevel(std::move(token));
                break;
        }
        // eat newline character that comes after
        std::cin.ignore();
    }
    return 0;
}
