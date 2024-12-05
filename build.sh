#!/bin/bash
if [ ! -d build ]; then
    mkdir build
fi

cd build

# CMAKE_EXPORT_COMPILE_COMMANDS for Clangd
cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    ..
make
src/main