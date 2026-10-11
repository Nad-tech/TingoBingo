# TingoBingo

TingoBingo is a Windows desktop prototype for **Tingo**, a cardboard robot. It is written in C++23 and uses raylib for its window, input, graphics, and audio. The project is being used to explore a component based character, procedural animation, robot state, and speech playback.

## Build and run

Build from the repository root in an MSYS2 MinGW64 terminal with `g++`, `mingw32-make`, and the raylib development libraries installed:

```bash
mingw32-make
```

The executable is `build/TingoBingo.exe`. Launch it with the repository root as the working directory so the relative image and audio paths resolve. The helper script builds and launches it:

```bash
./scripts/build.sh
```

Other Make targets:

```bash
mingw32-make clean
mingw32-make rebuild
```

## Controls

| Key | Action |
| --- | --- |
| `S` | Cycle the displayed brain state: Idle, Thinking, Listening, Searching, Reacting |
| `E` | Cycle the displayed emotion: None, Happy, Sad, Angry, Surprised |
| `G` | Toggle the speaking status |
| `1` | Toggle idle gesture flag |
| `2` | Toggle nod |
| `3` | Toggle head shake |
| `4` / `5` | Toggle left / right wave |
| `6` / `7` | Toggle left / right kick |
| `8` | Toggle jump |
| `9` | Toggle shrug |
| `0` | Toggle celebrate |
| `C` | Toggle crouch |
| `Z` | Toggle spin |
| `Q` / `W` | Close left / right eye |
| `A` / `D` | Close left / right clamp |
| `X` | Speak the greeting phrase |

The current brain state, emotion, speaking status, and gesture flags appear in the on-screen debug readout. These controls are useful for exercising the prototype; a state or gesture flag does not necessarily mean a complete animation or behavior is implemented for it.

## Project structure

```text
assets/                 Character, background, toy, voice, and sound assets
include/                Public headers
  Body/                 Body, head, arms, and legs component headers
src/                    C++ implementations and application entry point
  Body/                 Body, arm, and leg implementations
  Head/                 Head and facial component implementations
scripts/                Build and project utility scripts
tools/                  Bundled Piper and FFmpeg resources
utilities/              Project tree and source dump utilities
Makefile                MinGW build rules
```

The application starts in `src/main.cpp`. `Game` owns the raylib window and frame loop, handles input, and delegates updates and drawing to `Robot`. `Robot` owns `RobotState`, composes the body, and passes behavior work to `RobotBrain`. The body is split into head, arms, and legs, with smaller components responsible for their own transforms, updates, and drawing.

The main frame flow is:

```text
Initialise -> HandleInput -> Update -> Draw -> Shutdown
```

`RobotBrain` currently looks the robot at `{0, 0}`, manages idle timing and random idle phrases and gestures, and updates the speech controller. State and emotion cycling currently updates the debug display; it does not by itself implement state driven behavior or facial expressions. Gesture implementation varies by flag.

## Speech

Press `X` to request the greeting through the speech controller. `RobotBrain` can also request a random idle phrase after five seconds while its brain state is Idle and it is not speaking. Speech generation uses Piper and FFmpeg, with paths resolved from the project root:

```text
tools/piper/piper.exe
tools/piper/en_GB-alan-medium.onnx
tools/ffmpeg/bin/ffmpeg.exe
```

Piper generates a raw WAV, FFmpeg processes it, and raylib loads and plays the final file from `assets/audio/voice/speech.wav`. The required executables and model must be present at those paths for speech generation to work.

## Development notes

Add headers under `include/` and implementations under the matching `src/` subsystem, following the existing component lifecycle where practical. Build output is written under `build/`; do not edit generated files directly. Asset paths are relative to the project root.

There is no dedicated automated test suite. A successful build checks compilation; run the application to inspect visual, input, animation, and audio behavior.

## License

No project license is currently declared. Check with the author before redistributing the project or its bundled assets.
