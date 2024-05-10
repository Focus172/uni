#!/usr/bin/env nix-shell
#!nix-shell -i bash -p qt6.full gcc

mkdir -p build
cd build || exit
qmake ..
make
