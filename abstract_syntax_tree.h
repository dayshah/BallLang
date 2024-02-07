#ifndef AST_INCLUDED
#define AST_INCLUDED

#include <string>
#include <utility>
#include <vector>

namespace BallLang
{

struct ExprAST {
    virtual ~ExprAST() = default;
};

// number
struct NumberExprAST : public ExprAST {
    NumberExprAST(const double val): value(val) {}
    NumberExprAST(NumberExprAST&& numberExpr): value(numberExpr.value) {}

    double value;
};

// variableName
struct VariableExprAST : public ExprAST {
    VariableExprAST(std::string&& name): name(std::move(name)) {}
    VariableExprAST(VariableExprAST&& variableExpr):
        name(std::move(variableExpr.name)) {}

    std::string name;
};

// expression binop expression
struct BinaryExprAST : public ExprAST {
    BinaryExprAST(const char oper, ExprAST&& LHS, ExprAST&& RHS):
        oper(oper), LHS(std::move(LHS)), RHS(std::move(RHS)) {}

    BinaryExprAST(BinaryExprAST&& binaryExpr):
        oper(binaryExpr.oper), LHS(std::move(binaryExpr.LHS)), RHS(std::move(binaryExpr.RHS)) {}

    char oper;
    ExprAST LHS;
    ExprAST RHS;
};

// calleeName (args{expression}...)
struct CallExprAST : public ExprAST {
    CallExprAST(std::string&& callee, std::vector<ExprAST>&& args):
        callee(std::move(callee)), args(std::move(args)) {}

    CallExprAST(CallExprAST&& callExpr):
        callee(std::move(callExpr.callee)), args(std::move(callExpr.args)) {}

    std::string callee;
    std::vector<ExprAST> args; 
};

// functionName(args{strings}...)
struct PrototypeAST : public ExprAST {
    PrototypeAST(std::string&& name, std::vector<std::string>&& args):
        name(std::move(name)), args(std::move(args)) {}

    PrototypeAST(PrototypeAST&& prototype):
        name(std::move(prototype.name)), args(std::move(prototype.args)) {}

    std::string name;
    std::vector<std::string> args;
};

// prototype body
struct FunctionAST : public ExprAST {
    FunctionAST(PrototypeAST&& prototype, ExprAST&& body):
        prototype(std::move(prototype)), body(std::move(body)) {}

    FunctionAST(FunctionAST&& function):
        prototype(std::move(function.prototype)), body(std::move(function.body)) {}

    PrototypeAST prototype;
    ExprAST body;
};

}

#endif
