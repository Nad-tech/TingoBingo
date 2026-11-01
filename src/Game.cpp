#include "Game.h"
#include "raylib.h"

Game::Game() :
    world(inputController)
{}

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

    inputController.Initialise();
    world.Initialise(screenDimensions);
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        inputController.Update();

        float dt = GetFrameTime();

        world.Update(dt);

        BeginDrawing();

        ClearBackground(BLACK);

        world.Draw();

        if (inputController.IsConnected())
        {
            DrawText("CONTROLLER CONNECTED", 20, 20, 20, GREEN);
        }
        else
        {
            DrawText("CONTROLLER DISCONNECTED", 20, 20, 20, RED);
        }

        DrawText(
            TextFormat("Left X: %.2f  Y: %.2f",
                inputController.GetLeftStickX(),
                inputController.GetLeftStickY()),
            20, 50, 20, WHITE
        );

        DrawText(
            TextFormat("Right X: %.2f  Y: %.2f",
                inputController.GetRightStickX(),
                inputController.GetRightStickY()),
            20, 80, 20, WHITE
        );

        //DrawLegend();

        EndDrawing();
    }
}

void Game::Shutdown()
{
    world.ShutDown();

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
