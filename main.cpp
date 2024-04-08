
#include "lexer.h"
#include "parser.h"
#include <chrono>
#include <iostream>
#include <ostream>
#include <pstl/glue_execution_defs.h>
#include <ratio>
#include <string>
#include <vector>
#include <version>
#include <future>
#include <ranges>
#include <numeric>
#include <thread>
#include <execution>
#include "llvm/Config/abi-breaking.h"

// TODO: fix to build correctly eventually
int llvm::DisableABIBreakingChecks = 1;

int main() {

    // just to make it feel like something's happening
    const auto start = std::chrono::high_resolution_clock::now();
    int done = 0;
    std::vector<std::jthread> results{};
    for (int i = 0 ; i < 1000; ++i) {
        results.push_back(std::jthread([](){
            std::vector<int> nums{};
            for (int i = 100000; i > -1000; --i) {
                nums.push_back(i);
            }
            std::sort(nums.begin(), nums.end());
        }));
    }
    for (auto& result : results) result.join();
    const auto finish = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start).count() << std::endl;
    // it actually starts now...

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
