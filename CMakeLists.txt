cmake_minimum_required(VERSION 3.0)
project(
    md
    VERSION 0.1
    DESCRIPTION "Learning to implement a molecular dynamics code in C++")

set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20") ## Doesn't work on Windoze/VSCode
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
    md
    src/main.cpp
    src/particle.cpp
)