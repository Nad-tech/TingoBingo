# TingoBingo 3D V1

TingoBingo 3D V1 is a Windows C++23 and raylib prototype. It renders Tingo, a character assembled from individual GLB models, in a simple 3D room alongside a movable cube. Tingo animates automatically, including blinking, gaze movement, arm waves, sleep and wake cycles, and generated speech.

This is a character and rendering prototype; it does not currently implement bingo gameplay or menus.

## Features

- A perspective 3D scene with a floor, room walls, background image, lighting shaders, and a camera orientation indicator.
- A Tingo character built from separate body, head, arm, hand, leg, and facial feature models.
- A GLB cube that can be moved independently from Tingo.
- Procedural character behavior for blinking, looking around, waving, sleeping, and speaking.
- Piper text-to-speech and FFmpeg audio processing, with raylib audio playback.
- Gamepad input for moving and turning Tingo.

## Requirements

- Windows
- MinGW-w64 with a C++23 capable `g++` compiler and `mingw32-make`
- raylib development libraries and headers
- The raylib runtime DLLs `libraylib.dll` and `glfw3.dll` available beside the MinGW compiler
- Bash to run `Build.sh` (for example, Git Bash)

The build links raylib with `opengl32`, `gdi32`, and `winmm`. Speech generation uses the included Piper executable and voice model under `tools/piper/`, and FFmpeg under `tools/ffmpeg/`.

## Build and run

Run commands from the project root, `TingoBingo_3D_V1`. The application loads models, images, and speech tools using paths relative to its current working directory.

To compile the program and copy its raylib runtime DLLs into `build/`:

```bash
./Build.sh
```

Then launch it from the project root:

```bash
./build/TingoBingo_3D_V1.exe
```

Alternatively, use MinGW Make:

```bash
mingw32-make build/TingoBingo_3D_V1.exe
```

The default Make target is `all`, which builds and runs the application. `mingw32-make clean` removes generated objects, dependency files, the executable, and copied runtime DLLs.

## Controls

| Input | Action |
| --- | --- |
| `O` / `L` | Move Tingo along the Z axis |
| `K` / `;` | Move Tingo along the X axis |
| `R` / `F` | Move Tingo up / down |
| `Y` / `H` | Move the cube along the Z axis |
| `G` / `J` | Move the cube along the X axis |
| `Z` / `X` | Move the cube up / down |
| Gamepad left stick | Move Tingo horizontally; Tingo turns toward the movement direction |

The application disables the mouse cursor. The camera is currently fixed; free camera movement is disabled in the source. If a gamepad is connected, the window displays controller connection status and both stick axis values. The right stick is displayed but is not currently mapped to an action.

## Project structure

```text
assets/
  audio/       Generated speech audio
  images/      Space background and Tingo mouth sprite sheet
  models/      Tingo and game object GLB models
  shaders/     Lighting vertex and fragment shaders
include/       Application, world, input, character, and game object headers
src/           Main loop, world, input, character, speech, and rendering code
tools/         Bundled Piper and FFmpeg tools
Build.sh       Compile the application and copy raylib runtime DLLs
Makefile       MinGW Make build configuration
```

## Runtime behavior

`src/main.cpp` starts the application. `Game` creates the window, updates input, and runs the frame loop. `GameWorld` owns the camera, scene, Tingo character, and cube. Tingo's brain advances its autonomous behavior and speech controller each frame.

While idle, Tingo blinks, looks around, and waves periodically. It generates speech phrases, transitions into a sleep sequence after roughly 30 seconds, and returns to idle after the sleep animation. Speech generation writes intermediate and processed WAV files under `assets/audio/voice/`.

## Assets and tools

Model and image loading uses `assets/` paths from the project root. Speech generation expects these bundled files:

```text
tools/piper/piper.exe
tools/piper/en_GB-alan-medium.onnx
tools/ffmpeg/bin/ffmpeg.exe
```

Raylib handles playback of the generated speech. Keep the application's working directory at the project root so asset and tool paths resolve correctly.
