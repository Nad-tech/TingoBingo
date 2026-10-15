#!/usr/bin/env bash

set -e

echo "Building Tingo Bingo 3D Version 1..."

mkdir -p build

compiler_dir="$(dirname "$(command -v g++)")"
runtime_dlls=(
	"$compiler_dir/libraylib.dll"
	"$compiler_dir/glfw3.dll"
)

for dll in "${runtime_dlls[@]}"; do
	if [[ ! -f "$dll" ]]; then
		echo "Required runtime DLL not found: $dll" >&2
		exit 1
	fi
done

sources=()
while IFS= read -r -d '' source; do
	sources+=("$source")
done < <(find src -name '*.cpp' -print0)

g++ -std=c++23 \
	-Wall -Wextra \
	-g \
	-Iinclude \
	"${sources[@]}" \
	-o build/TingoBingo_3D_V1.exe \
	-lraylib \
	-lopengl32 \
	-lgdi32 \
	-lwinmm \
	-mconsole

cp "${runtime_dlls[@]}" build/

echo "Build successful!"