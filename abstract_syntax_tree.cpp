
#include <map>
#include <memory>
#include <llvm/ADT/APFloat.h>
#include <llvm/ADT/STLExtras.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Verifier.h>
#include "abstract_syntax_tree.h"

namespace BallLang {

static std::unique_ptr<llvm::LLVMContext> CONTEXT;
static std::unique_ptr<llvm::Module> MODULE;
static std::unique_ptr<llvm::IRBuilder<>> BUILDER(std::make_unique<llvm::IRBuilder<>>(*CONTEXT));
std::map<std::string, llvm::Value*> namedValues;

ExprAST::~ExprAST() {}

llvm::Value* ExprAST::codegen() {
    return nullptr; // TODO: remove with the implementation of concepts
}

llvm::Value* NumberExprAST::codegen() {
    return nullptr;
}

llvm::Value* BinaryExprAST::codegen() {
    return nullptr;
}

llvm::Value* CallExprAST::codegen() {
    return nullptr;
}

llvm::Value* PrototypeAST::codegen() {
    return nullptr;
}

llvm::Value* FunctionAST::codegen() {
    return nullptr;
}

llvm::Value* VariableExprAST::codegen() {
    return nullptr;
}

};
