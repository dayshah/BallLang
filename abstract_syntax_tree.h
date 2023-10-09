#ifndef AST_INCLUDED
#define AST_INCLUDED

#include <string>

class ExprAST {
    public:
    virtual ~ExprAST() = default;
};

class NumberExprAST : public ExprAST {
    public:
    NumberExprAST(double val): value(val)
    {} 
    
    const double value;
};

class VariableExprAST : ExprAST {
    public:
    VariableExprAST(const std::string& name): name(name)
    {}

    const std::string name;
};

class BinaryExprAST : ExprAST {
    public:
    BinaryExprAST(char oper, const ExprAST* const LHS, const ExprAST* const RHS):
        oper(oper), LHS(LHS), RHS(RHS)
    {}

    const char oper;
    const ExprAST* const LHS;
    const ExprAST* const RHS;
};

class CallExprAST : public ExprAST {
    public:
    CallExprAST(const std::string& callee, const std::vector<ExprAST>* const args):
        callee(callee), args(args)
    {}

    const std::string callee;
    const std::vector<ExprAST>* const args; 
};

class PrototypeAST : public ExprAST {
    public:
    PrototypeAST(const std::string& name, const std::vector<std::string>* const args):
        name(name), args(args)
    {}

    const std::string name;
    const std::vector<std::string>* const args;
};

class FunctionAST : public ExprAST {
    public:
    FunctionAST(const PrototypeAST* const prototype, const ExprAST* const body):
        prototype(prototype), body(body)
    {}

    const PrototypeAST* const prototype;
    const ExprAST* const body;
};

#endif
