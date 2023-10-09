
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"

ExprAST parsePrimary() {
    TokenValue current = getTokenValue();
    switch(current.type) {
        case IDENTIFIER:
            if (current.stringVal.has_value())
                return parseIdentifier(current.stringVal.value());
            else throw "ERROR: No stringVal in IDENTIFIER TokenValue";
        case NUMBER:
            if (current.doubleVal.has_value())
                return NumberExprAST(current.doubleVal.value());
            else throw "ERROR: No doubleVal in NUMBER TokenValue";
        default:
            throw "bro i dont know";

    }
}

ExprAST parseIdentifier(const std::string& identifier) {
    
}
