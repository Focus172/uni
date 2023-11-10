
default:
    @just -l

# clang {{src_files}} -o build/uni -Wall -Wextra -Werror -O2 -pedantic

# Builds all the code using cmake
cmake:
    #!/bin/sh
    mkdir -p build
    cd build
    cmake ..
    make all

sbuild:
    @just cmake > /dev/null

run: sbuild
    ./build/uni 'test input' 'data'

hw1: sbuild
    ./build/hw1-sol1
    ./build/hw1-sol2

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

hw4: sbuild
    ./build/hw4-p1

hw5: sbuild
    ./build/hw5

lab7:
    @just cmake > /dev/null
    ./build/lab7

hw6: sbuild
    ./build/hw6

hw7: sbuild
    ./build/hw7

lab8: sbuild
    ./build/lab8

