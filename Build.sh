#!/usr/bin/env bash

set -e

echo "Building Tingo Bingo 3D Version 1..."

mkdir -p build

g++ -std=c++23 \
	-Wall -Wextra \
	-g \
	-Iinclude \
	src/*.cpp \
	-o build/TingoBingo_3D_V1.exe \
	-lraylib \
	-lopengl32 \
	-lgdi32 \
	-lwinmm \
	-mconsole

echo "Build successful!"