#include "Game.h"
#include "raylib.h"

void Game::Initialise()
{
    InitWindow(10, 10, "TingoBingo 3D");

    int monitor = GetCurrentMonitor();
    int width = GetMonitorWidth(monitor);
    int height = GetMonitorHeight(monitor);

    screenDimensions.screenWidth = width;
    screenDimensions.screenHeight = height;

    SetWindowSize(width, height);
    SetWindowPosition(0, 0);

    SetTargetFPS(60);
    DisableCursor();

    world.Initialise(screenDimensions);
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        world.Update(dt);

        BeginDrawing();

        ClearBackground(RAYWHITE);

        world.Draw();

        EndDrawing();
    }
}

void Game::Shutdown()
{
    world.Shutdown();

    CloseWindow();
}
