#ifndef AST_INCLUDED
#define AST_INCLUDED

#include <llvm/Config/abi-breaking.h>
#include <string>
#include <utility>
#include <vector>

#include "llvm/IR/DerivedTypes.h"

namespace BallLang
{

struct ExprAST { // move to concept eventually for runtime perf
    ~ExprAST() = default;
    //virtual llvm::Value *codegen();
};

// number
struct NumberExprAST : public ExprAST {
    NumberExprAST(const double val):
        value(val)
    {}

    double value;

    //llvm::Value *codegen() override;
};

// variableName
struct VariableExprAST : public ExprAST {
    VariableExprAST(std::string&& name):
        name(std::move(name)) 
    {}

    std::string name;

    //llvm::Value *codegen() override;
};

// expression binop expression
struct BinaryExprAST : public ExprAST {
    BinaryExprAST(const char oper, ExprAST&& LHS, ExprAST&& RHS):
        oper(oper), LHS(std::move(LHS)), RHS(std::move(RHS)) 
    {}

    char oper;
    ExprAST LHS;
    ExprAST RHS;

    //llvm::Value *codegen() override;
};

// calleeName (args{expression}...)
struct CallExprAST : public ExprAST {
    CallExprAST(std::string&& callee, std::vector<ExprAST>&& args):
        callee(std::move(callee)), args(std::move(args))
    {}

    std::string callee;
    std::vector<ExprAST> args;

    //llvm::Value *codegen() override;
};

// functionName(args{strings}...)
struct PrototypeAST : public ExprAST {
    PrototypeAST(std::string&& name, std::vector<std::string>&& args):
        name(std::move(name)), args(std::move(args))
    {}

    std::string name;
    std::vector<std::string> args;

    //llvm::Value *codegen() override;
};

// prototype body
struct FunctionAST : public ExprAST {
    FunctionAST(PrototypeAST&& prototype, ExprAST&& body):
        prototype(std::move(prototype)), body(std::move(body))
    {}

    PrototypeAST prototype;
    ExprAST body;

    //llvm::Value *codegen() override;
};

}

#endif
