cmake_minimum_required(VERSION 3.27)
project(FishDB)

set(CMAKE_CXX_STANDARD 17)

add_executable(FishDB Lexer.h Lexer.cpp main.cpp utility.h)
