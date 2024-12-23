#!/bin/bash

# Get project's root directory
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

# Create a build directory if not already exists
if [ ! -d build ]; then
    mkdir build
fi
cd build

# Build the project
# CMAKE_EXPORT_COMPILE_COMMANDS for Clangd
# CMAKE_PREFIX_PATH for Abseil and re2
cmake \
    -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DCMAKE_PREFIX_PATH="$SCRIPT_DIR/install/" \
    ..
make
src/main