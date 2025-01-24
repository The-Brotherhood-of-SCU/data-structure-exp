cmake_minimum_required(VERSION 3.28)
project(exp1)

set(CMAKE_CXX_STANDARD 17)

add_executable(simpleMatlib main.cpp
        ExpressionHandler.h
        AstNode.h
        Exception.h
        Interface.h
        Utils.h
)
