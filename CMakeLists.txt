cmake_minimum_required(VERSION 3.27)
project(FishDB)
set(CMAKE_CXX_STANDARD 20)

aux_source_directory(src/Storage _SOURCES)

add_executable(FishDB Lexer.h Lexer.cpp main.cpp utility.h
        tools/parse.cpp tools/parse.h ${_SOURCES})

target_include_directories(FishDB PRIVATE include/Storage)
