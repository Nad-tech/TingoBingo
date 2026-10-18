# TingoBingo 3D V1

TingoBingo 3D V1 is a small C++ application built with [raylib](https://www.raylib.com/). It renders Tingo, a character assembled from separate 3D model parts, inside a simple room. The project is an exploration of 3D character construction, hierarchical transforms, lighting, and camera movement.

## What it includes

- A Tingo character assembled from GLB models for the body, head, arms, hands, legs, and facial features.
- A perspective 3D scene with a floor, three walls, a grid, and a space background image.
- A custom shader for directional lighting and ambient illumination.
- A mouth sprite sheet and a screen-space camera orientation gizmo.
- A free-moving raylib 3D camera. The cursor is disabled while the application runs.

The current application is a visual and animation prototype; it does not include bingo gameplay or menus.

## Requirements

- Windows
- A C++23 MinGW-w64 toolchain with `g++` and `mingw32-make`
- raylib development files and runtime DLLs (`libraylib.dll` and `glfw3.dll`)
- Bash to use `Build.sh` (for example, Git Bash) or Make to use the `Makefile`

The build scripts expect the compiler and raylib libraries to be available in the toolchain environment. The Makefile links against `raylib`, `opengl32`, `gdi32`, and `winmm`.

## Build and run

Open a terminal in the project directory so the relative asset paths resolve correctly.

With Bash:

```bash
./Build.sh
```

This compiles all `.cpp` files under `src/`, places the executable and raylib runtime DLLs in `build/`, and reports whether the build succeeded. Run the program with:

```bash
./build/TingoBingo_3D_V1.exe
```

With MinGW Make:

```bash
mingw32-make
```

The default `all` target builds and runs `build/TingoBingo_3D_V1.exe`. To build without starting the application, use:

```bash
mingw32-make build/TingoBingo_3D_V1.exe
```

## Project layout

```text
assets/
  images/       Background and mouth sprite sheet
  models/       Tingo GLB models and Blender source files
  shaders/      Vertex and fragment lighting shaders
include/        Game, world, character, dimensions, and transform headers
src/            Application loop, 3D world, animation, and character parts
scripts/        Build and project-inspection helper scripts
Build.sh        Bash build script
Makefile        MinGW Make build configuration
```

The application starts in `src/main.cpp`. `Game` owns the main loop, `GameWorld` manages the camera and scene, and `Tingo` delegates character updates and drawing to the body-part hierarchy. Model and image paths are relative to the project root.
