#!/bin/bash
set -e

# Remove the old build, add the new build
rm -rf build/
mkdir build
cd build/

# Run cmake
if ! cmake --fresh ..; then
    echo "cmake configuration failed. Cleaning up..."
    cd ..
    rm -rf build/
    exit 1
fi

# Normalize timestamps

find . -type f -exec touch {} +
sleep 1

# Run build
if ! cmake --build . --clean-first; then
    echo "cmake build failed. Cleaning up..."
    cd ..
    rm -rf build/
    exit 1
fi

# Run program
./RISK_sim