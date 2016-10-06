cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_COMPILER clang++-3.5)
project(cpp-exam)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set(EXECUTABLE cpp-exam)

add_compile_options(-std=c++14)

file(
    GLOB
    sources
    src/*
)

include_directories(includes)

add_executable(
    ${EXECUTABLE}
    src/main.cpp
    ${sources}
)
