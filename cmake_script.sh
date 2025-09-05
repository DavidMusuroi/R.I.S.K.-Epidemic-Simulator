#!/bin/bash
set -e

# Remove old build and add new build
rm -rf build/
mkdir build
cd build/

# Run cmake
if ! cmake ..; then
    echo "cmake configuration failed. Cleaning up..."
    cd ..
    rm -rf build/
    exit 1
fi

# Run build
if ! cmake --build .; then
    echo "cmake build failed. Cleaning up..."
    cd ..
    rm -rf build/
    exit 1
fi

# Run the program
./RISK_sim