
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

lab2: sbuild
    ./build/lab2-sol1
    ./build/lab2-sol2

lab4: sbuild
    ./build/lab4-sol1
    ./build/lab4-sol2

lab number: sbuild
    ./build/lab{{number}}

hw number: sbuild
    ./build/hw{{number}}

