cmake_minimum_required(VERSION 3.5)

project(uni LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main src/main.cpp)
add_executable(hw1-p1 src/hw1/p1.cpp)
add_executable(hw1-p3 src/hw1/p3.cpp)

add_executable(hw2-p1 src/hw2/p1.cpp)
add_executable(hw2-p2 src/hw2/p2.cpp)
add_executable(hw2-p3 src/hw2/p3.cpp)
add_executable(hw2-p4 src/hw2/p4.cpp)

add_executable(hw3-p2 src/hw3/p2.cpp)

add_executable(hw4-p1 src/hw4/p1.cpp)
add_executable(hw4-p2 src/hw4/p2.cpp)
