
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"

ExprAST parsePrimary() {
    TokenValue current = getTokenValue();
    switch(current.type) {
        case IDENTIFIER:
            if (current.stringVal.has_value())
                return NumberExprAST(current.doubleVal.value());//parseIdentifier(current.stringVal.value());
            else throw "ERROR: No stringVal in IDENTIFIER TokenValue";
        case NUMBER:
            if (current.doubleVal.has_value())
                return NumberExprAST(current.doubleVal.value());
            else throw "ERROR: No doubleVal in NUMBER TokenValue";
        case DEF:
        case EXTERN:
        case ERROR:
            throw "ERROR: TokenValue got set to error...";
        default:
            throw "bro i dont know";
    }
}

// ExprAST parseIdentifier(const std::string& identifier) {
// }
