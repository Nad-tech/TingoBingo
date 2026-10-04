# TingoBingo

TingoBingo is a Windows desktop prototype for building and animating Tingo, a cardboard robot. It is written in C++23 and uses raylib for the window, drawing, input, and audio playback.

The project is currently a hands-on animation and architecture prototype. The robot is assembled from separate body parts, and keyboard controls expose its state and several gesture animations for development.

## Run the Prototype

Build and launch from an MSYS2 MinGW64 terminal at the repository root:

```bash
./scripts/build.sh
```

To build without launching:

```bash
mingw32-make
```

The executable is created at `build/TingoBingo.exe`. Run it with the repository root as the working directory, because images and audio are loaded using paths relative to that directory.

### Build Requirements

- Windows
- [MSYS2](https://www.msys2.org/) with the MinGW64 environment
- GCC/G++, `mingw32-make`, and raylib development libraries available in that environment

Other Makefile targets:

```bash
mingw32-make clean      # Remove generated object, dependency, and executable files
mingw32-make rebuild    # Clean and build again
```

## Keyboard Reference

| Key | Effect |
| --- | --- |
| `S` | Cycle the displayed robot state: Idle, Thinking, Listening, Reacting |
| `E` | Cycle the displayed emotion: Idle, Happy, Sad, Angry, Surprised |
| `G` | Toggle the speaking status indicator |
| `1` | Toggle the idle gesture flag |
| `2` | Nod |
| `3` | Toggle the head-shake gesture flag |
| `4` / `5` | Wave the left / right arm |
| `6` / `7` | Toggle the left / right kick gesture flags |
| `8` | Toggle the jump gesture flag |
| `9` | Shrug |
| `0` | Toggle the celebrate gesture flag |
| `C` | Crouch |
| `Z` | Toggle the spin gesture flag |

The current state, emotion, speaking value, and gesture flags are shown in the on-screen debug readout. State, emotion, and speaking inputs currently update that readout; they do not yet drive a behaviour system. Nod, crouch, arm wave, and shrug have animation code. Several other gesture flags are present as controls and state, but do not yet have a completed animation.

## What Is in the Code

The application is organised around a frame loop in `Game`:

```text
Initialise → HandleInput → Update → Draw → Shutdown
```

`Game` creates the raylib window and audio device, loads the background, handles keyboard input, and updates and draws the robot. `Robot` owns the robot's state and composes the body. `Body`, `Head`, `Arms`, and `Legs` delegate transforms, animation updates, and drawing to their component classes.

The head is made from a head base, eyes and pupils, eyebrows, mouth, nose, ears, and antenna. The arms include shoulders, upper arms, elbows, forearms, hands, fingers, and clamps. The legs are split into thighs, knees, shins, and feet. Shared transform and shape types support component placement and rendering.

`RobotBrain` is the intended home for higher-level behaviour, but its update method is currently empty. The state and emotion values can be cycled for inspection; autonomous reactions and transitions have not yet been implemented.

## Speech Experiment

Speech support is present in `SpeechGenerator` and `SpeechController`. The intended pipeline generates a WAV with Piper on a worker thread, processes it with FFmpeg, then loads and plays the result through raylib on the main thread.

Speech generation expects these paths relative to the repository root:

```text
tools/piper/piper.exe
tools/piper/en_GB-alan-medium.onnx
tools/ffmpeg/bin/ffmpeg.exe
```

The voice model and supporting speech resources are in the repository, but the expected Piper and FFmpeg executables must also be available at those paths. Speech is not currently triggered by the game loop.

## Repository Map

```text
assets/                 Robot and background images, audio files
include/                Public headers for game and robot components
  Body/Head/            Head and facial component headers
  Body/Arms/            Arm, hand, finger, and clamp headers
  Body/Legs/            Leg component headers
src/                    C++ implementations and application entry point
  head/                 Head and facial components
  body/                 Body, head, arms, and legs
scripts/                Build and project utility scripts
tools/                  Piper and FFmpeg resources
utilities/              Project tree and source dump utilities
Makefile                MinGW build rules
build/                  Generated compiler output
```

## Development

Add component headers under `include/` and implementations under the matching `src/` subsystem. The Makefile discovers application, head, body, arm, and leg `.cpp` files and places generated output in `build/`.

There is no automated test suite at present. A successful `mingw32-make` build checks compilation; run the executable to inspect visual and animation changes.

## License

No license is declared. Contact the author before redistributing this project or its bundled assets.
