#ifndef AST_INCLUDED
#define AST_INCLUDED

#include <string>

namespace BallLang
{

struct ExprAST {
    virtual ~ExprAST() = default;
};

struct NumberExprAST :  ExprAST {
    NumberExprAST(double val): value(val) {}

    const double value;
};

struct VariableExprAST : ExprAST {
    VariableExprAST(const std::string& name): name(name) {}

    const std::string name;
};

struct BinaryExprAST : public ExprAST {
    BinaryExprAST(char oper, const ExprAST LHS, const ExprAST RHS):
        oper(oper), LHS(LHS), RHS(RHS) {}

    const char oper;
    const ExprAST LHS;
    const ExprAST RHS;
};

class CallExprAST : public ExprAST {
    CallExprAST(const std::string& callee, const std::vector<ExprAST>* const args):
        callee(callee), args(args) {}

    const std::string callee;
    const std::vector<ExprAST>* const args; 
};

struct PrototypeAST : public ExprAST {
    PrototypeAST(const std::string& name, const std::vector<std::string>* const args):
        name(name), args(args) {}

    const std::string name;
    const std::vector<std::string>* const args;
};

struct FunctionAST : public ExprAST {
    FunctionAST(const PrototypeAST prototype, const ExprAST body):
        prototype(prototype), body(body) {}

    const PrototypeAST prototype;
    const ExprAST body;
};

}

#endif
