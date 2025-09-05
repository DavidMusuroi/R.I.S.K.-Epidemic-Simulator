#!/bin/bash
set -e

# Remove the old build, add the new build and normalize timestamps
find . -type f -exec touch {} +
sleep 1
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

# Run program
./RISK_sim