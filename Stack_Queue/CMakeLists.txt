cmake_minimum_required(VERSION 4.1)
project(Stack_Queue)

set(CMAKE_CXX_STANDARD 20)

add_executable(Stack_Queue main.cpp
        Queue.cpp
        Queue.h
        Stack.cpp
        Stack.h)
