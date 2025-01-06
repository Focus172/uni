#!/bin/sh

mkdir -p build
cd build || exit 1
qmake ..
make
