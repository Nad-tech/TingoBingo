#include "Game.h"
#include "raylib.h"

void Game::Initialise()
{
    InitWindow(800, 600, "Tingo Bingo 3D Version 1");
    SetTargetFPS(60);

    DisableCursor();  // Keep the mouse captured inside the game window

    world.Initialise();
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