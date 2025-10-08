#!/bin/bash
set -e

# Remove the old build and add the new build
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

# Forced QT to use X11
export QT_QPA_PLATFORM=xcb

#Run GUI
python3 ../gui/gui.py