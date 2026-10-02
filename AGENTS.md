# AGENTS.md

This repository is a Windows desktop prototype for TingoBingo, built in C++ with raylib and targeted at the MSYS2 MinGW64 toolchain.

## Project context

- Primary app entry: [src/main.cpp](src/main.cpp)
- Main loop and scene orchestration: [src/Game.cpp](src/Game.cpp) and [include/Game.h](include/Game.h)
- Robot behaviour and composition: [src/Robot.cpp](src/Robot.cpp) and [include/Robot.h](include/Robot.h)
- Supporting docs: [README.md](README.md), [Makefile](Makefile), and [scripts/build.sh](scripts/build.sh)

## Build and validation

Use the repo’s native build flow instead of ad hoc compilation commands.

- Build the project: `mingw32-make`
- Build and launch the app: `./scripts/build.sh`
- Clean generated files: `mingw32-make clean`
- Rebuild from scratch: `mingw32-make rebuild`

There are no dedicated automated tests in this repository. The practical validation step is a successful build, and for gameplay changes a focused run of the executable is the final check.

## Architecture conventions

- The game loop is organized around `Game::Initialise()`, `HandleInput()`, `Update()`, `Draw()`, and `Shutdown()`.
- `Game` owns the application lifetime and delegates gameplay to `Robot`.
- `Robot` composes modular body and head subsystems, with behavior logic grouped in `RobotBrain` and animation/render logic split across component classes.
- Subsystems generally follow the same lifecycle pattern: initialise, update, draw, and shutdown.
- Header files live under [include/](include/), implementation files under [src/](src/), and generated output is emitted under [build/](build/).

## Coding conventions

- Keep new logic consistent with the existing component-per-responsibility design.
- Prefer small, focused additions over large refactors unless the work is specifically restructuring a subsystem.
- Match the current naming and style of the surrounding code: classes are used for game systems, and helper data sits in the relevant header/source pair.
- Preserve the current lifecycle conventions; do not add one-off patterns that bypass `Initialise`/`Update`/`Draw`/`Shutdown`.
- Do not edit generated build artifacts directly; these are produced by the compiler.

## Suggestions for future work

- When adding a new feature, keep it modular and map it cleanly onto the existing `Game` → `Robot` → subsystem hierarchy.
- For gameplay or AI behavior, prefer changes that fit the current `RobotBrain`/emotion/state flow rather than introducing a separate, parallel system.
- For new assets or speech/tool integrations, keep resource paths relative to the project root and document the dependency in the relevant source or README section.

## Related customization guidance

This file is intentionally minimal and points agents to the project’s existing documentation rather than duplicating it. If the repo grows, consider creating a more focused instruction file for gameplay systems or speech/animation tooling.
