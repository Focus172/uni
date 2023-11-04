
src_files := 'src/main.cpp'
CC := 'clang'

default:
    @just -l

# Builds all the code using clang
build:
    mkdir -p build
    {{CC}} {{src_files}} -o build/uni # -Wall -Wextra -Werror -O2 -pedantic

# Builds all the code using cmake
cmake:
    #!/bin/sh
    mkdir -p build
    cd build
    cmake ..
    make all

# Builds and runs the main function of this repo, mostly a note taking file
run:
    @just cmake > /dev/null
    ./build/uni 'test input' 'data'

# nim:
#     nim r src/main.nim

# Builds and runs the first homework assignment
hw1:
    @just cmake > /dev/null
    ./build/hw1-sol1
    ./build/hw1-sol2

# Builds and runs the second homework assignment
hw2:
    @just cmake > /dev/null
    ./build/hw2-sol2

lab2:
    @just cmake > /dev/null
    ./build/lab2-sol1
    ./build/lab2-sol2

lab3:
    @just cmake > /dev/null
    ./build/lab3-sol1

lab4:
    @just cmake > /dev/null
    ./build/lab4-sol1
    ./build/lab4-sol2

lab5:
    @just cmake > /dev/null
    ./build/lab5-sol1

hw4:
    @just cmake > /dev/null
    ./build/hw4-sol1

hw5:
    @just cmake > /dev/null
    ./build/hw5

lab7:
    @just cmake > /dev/null
    ./build/lab7

hw6:
    @just cmake > /dev/null
    ./build/hw6

hw7:
    @just cmake > /dev/null
    ./build/hw7
