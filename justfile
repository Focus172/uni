
src_files := 'main.cpp'
CC := 'clang'

default:
    @just -l

# Builds all the code using clang
build:
    mkdir -p build
    # zig cc {{src_files}} -o build/uni
    {{CC}} {{src_files}} -o build/uni -Wall -Wextra -Werror -O2 -pedantic

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
