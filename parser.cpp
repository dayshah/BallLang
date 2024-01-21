
#include "lexer.h"
#include "abstract_syntax_tree.h"
#include "parser.h"

namespace BallLang
{

ExprAST parsePrimary() {
    TokenValue current = getTok();
    switch(current.type) {
        case IDENTIFIER:
            if (const std::string* value = std::get_if<std::string>(&current.value))
                return VariableExprAST(*value);
            else 
                throw "ERROR: No stringVal in IDENTIFIER TokenValue";
        case NUMBER:
            if (const double* value = std::get_if<double>(&current.value))
                return NumberExprAST(*value);
            else 
                throw "ERROR: No doubleVal in NUMBER TokenValue";
        case DEF:
        case EXTERN:
        case ERROR:
            throw "ERROR: TokenValue got set to error...";
        default:
            throw "bro i dont know";
    }
}

PrototypeAST parsePrototype(const std::string& token) {
    
}

}
