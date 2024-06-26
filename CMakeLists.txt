cmake_minimum_required(VERSION 3.20.0)

project(
    BallLang
    VERSION 1.0
    LANGUAGES C CXX
)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_COMPILER "clang++")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_executable(BallLang main.cpp parser.cpp lexer.cpp abstract_syntax_tree.cpp)

llvm_map_components_to_libnames(llvm_libs support core irreader)

target_link_libraries(BallLang ${llvm_libs})

target_include_directories(
    BallLang PUBLIC
    "${PROJECT_BINARY_DIR}"
)
