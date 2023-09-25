
src_files := 'main.cpp'
CC := 'clang'

default:
    @just -l

build:
    mkdir -p build
    # zig cc {{src_files}} -o build/uni
    {{CC}} {{src_files}} -o build/uni -Wall -Wextra -Werror -O2 -pedantic

cmake:
    #!/bin/sh
    mkdir -p build
    cd build
    cmake ..
    make all

run:
    @just cmake > /dev/null
    ./build/uni 'test input' 'data'

nim:
    nim r src/main.nim

hw1:
    @just cmake > /dev/null
    ./build/hw1-sol1
    ./build/hw1-sol2
