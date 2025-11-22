#!/bin/bash

# Path to the directory of this script
DIR="$(cd "$(dirname "$0")" && pwd)"

# Compile everything
g++ -std=c++17 \
    "$DIR/main.cpp" "$DIR"/Core/*.cpp \
    -o "$DIR/game" \
    $(sdl2-config --cflags --libs) \
    -lSDL2_image -lSDL2_gfx

# If compile succeeded, run the program
if [ $? -eq 0 ]; then
    echo "Build successful! Running..."
    "$DIR/game"
else
    echo "Build failed."
fi
 