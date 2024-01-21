cmake_minimum_required(VERSION 3.5)

project(
    BallLang
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER "clang++")

add_executable(BallLang main.cpp parser.cpp lexer.cpp)

target_include_directories(
    BallLang PUBLIC
    "${PROJECT_BINARY_DIR}"
)