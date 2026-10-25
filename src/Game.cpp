#include "Game.h"
#include "raylib.h"

void Game::Initialise()
{
    InitWindow(10, 10, "TingoBingo 3D");

    InitAudioDevice();

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

        ClearBackground(BLACK);

        world.Draw();

        //DrawLegend();

        EndDrawing();
    }
}

void Game::Shutdown()
{
    world.Shutdown();

    CloseAudioDevice();

    CloseWindow();
}

void Game::DrawLegend()
{
    const int legendX = screenDimensions.screenWidth - 350;
	const int legendY = 150;
	const int legendWidth = 335;
	const int legendHeight = 310;
	const int lineHeight = 20;
    const int columnWidth = 160;
	int textY = legendY + 10;
    int textX = legendX + 10;

	DrawRectangle(
		legendX,
		legendY,
		legendWidth,
		legendHeight,
		Fade(BLACK, 0.75f)
	);
	DrawRectangleLines(legendX, legendY, legendWidth, legendHeight, Fade(RAYWHITE, 0.5f));

	DrawText("KEY BINDINGS", textX, textY, 18, YELLOW);
	textY += lineHeight;
	DrawText("Wave right: 1", textX, textY, 14, RAYWHITE);
    textX += columnWidth;
	DrawText("Wave left: 2", textX, textY, 14, RAYWHITE);
}
