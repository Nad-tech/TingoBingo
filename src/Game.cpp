//====================================================
// Game.cpp
//
// Controls the main game loop.
//
// The Game class is responsible for initialising the
// application, processing input, updating the game
// state, drawing each frame and shutting everything
// down when the program exits.
//====================================================

// Main game loop.
//
// Initialise()
//       │
//       ▼
// ┌─────────────────────┐
// │ HandleInput()       │
// │ Update()            │
// │ BeginDrawing()      │
// │ Draw()              │
// │ EndDrawing()        │
// └─────────────────────┘
//          ▲
//          │
// WindowShouldClose()
//          │
// Shutdown()

#include "raylib.h"

#include "Game.h"
#include "Constants.h"
#include "MyTransform.h"


void Game::Initialise()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();

    // Initialise robot
	robotWorldPos = {0, 30.0f};
    
	MyTransform initialTransform
	{
		.position = robotWorldPos,
		.rotation = 0.0f,
		.scale = SCALE
	};

	robot.Initialise();
	robot.SetTransform(initialTransform);

    SetTargetFPS(TARGET_FPS);

    background = LoadTexture(
        "assets/images/background/space.jpg"
    );
}

void Game::HandleInput()
{
	if (input.S_Pressed()) robot.CycleState();
	if (input.E_Pressed()) robot.CycleEmotion();
	if (input.G_Pressed()) robot.ToggleSpeaking();

	if (IsKeyPressed(KEY_ONE)) robot.ToggleGesture("idle");
	if (IsKeyPressed(KEY_TWO)) robot.ToggleGesture("nod");
	if (IsKeyPressed(KEY_THREE)) robot.ToggleGesture("shakeHead");
	if (IsKeyPressed(KEY_FOUR)) robot.ToggleGesture("waveLeft");
	if (IsKeyPressed(KEY_FIVE)) robot.ToggleGesture("waveRight");
	if (IsKeyPressed(KEY_SIX)) robot.ToggleGesture("kickLeft");
	if (IsKeyPressed(KEY_SEVEN)) robot.ToggleGesture("kickRight");
	if (IsKeyPressed(KEY_EIGHT)) robot.ToggleGesture("jump");
	if (IsKeyPressed(KEY_NINE)) robot.ToggleGesture("shrug");
	if (IsKeyPressed(KEY_ZERO)) robot.ToggleGesture("celebrate");
	if (IsKeyPressed(KEY_C)) robot.ToggleGesture("crouch");
	if (IsKeyPressed(KEY_Z)) robot.ToggleGesture("spin");
	if (IsKeyPressed(KEY_Q)) robot.ToggleGesture("closeLeftEye");
	if (IsKeyPressed(KEY_W)) robot.ToggleGesture("closeRightEye");
    if (IsKeyPressed(KEY_A)) robot.ToggleGesture("closeLeftClamp");
    if (IsKeyPressed(KEY_D)) robot.ToggleGesture("closeRightClamp");
}

void Game::Update(const float dt)
{	
	robot.Update(dt);
}

void Game::Draw()
{
	ClearBackground(BLACK);

	DrawTexture(background, 0, 0, WHITE);

	robot.Draw();

	const int legendX = SCREEN_WIDTH - 292;
	const int legendY = 12;
	const int legendWidth = 280;
	const int lineHeight = 20;
	const int textX = legendX + 10;
	const int rightColumnX = legendX + 148;
	int textY = legendY + 10;

	DrawRectangle(
		legendX,
		legendY,
		legendWidth,
		250,
		Fade(BLACK, 0.75f)
	);
	DrawRectangleLines(legendX, legendY, legendWidth, 250, Fade(RAYWHITE, 0.5f));

	DrawText("KEY BINDINGS", textX, textY, 18, YELLOW);
	textY += lineHeight + 2;
	DrawText("S  Cycle state", textX, textY, 14, RAYWHITE);
	DrawText("E  Cycle emotion", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("G  Toggle speaking", textX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("GESTURES", textX, textY, 14, YELLOW);
	textY += lineHeight;

	DrawText("1  Idle", textX, textY, 14, RAYWHITE);
	DrawText("2  Nod", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("3  Shake head", textX, textY, 14, RAYWHITE);
	DrawText("4  Wave left", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("5  Wave right", textX, textY, 14, RAYWHITE);
	DrawText("6  Kick left", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("7  Kick right", textX, textY, 14, RAYWHITE);
	DrawText("8  Jump", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("9  Shrug", textX, textY, 14, RAYWHITE);
	DrawText("0  Celebrate", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("C  Crouch", textX, textY, 14, RAYWHITE);
	DrawText("Z  Spin", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("Q  Close left eye", textX, textY, 14, RAYWHITE);
	DrawText("W  Close right eye", rightColumnX, textY, 14, RAYWHITE);
	textY += lineHeight;
	DrawText("A  Close left clamp", textX, textY, 14, RAYWHITE);
	DrawText("D  Close right clamp", rightColumnX, textY, 14, RAYWHITE);
}

void Game::Shutdown()
{
	robot.Shutdown();

	UnloadTexture(background);

	CloseAudioDevice();

	CloseWindow();
}

// Run the main game loop.
void Game::Run()
{
	float dt = GetFrameTime();

	Initialise();

	while (!WindowShouldClose())
	{
		HandleInput();

		dt = GetFrameTime();
		Update(dt);

		BeginDrawing();

		Draw();

		EndDrawing();
	}

	Shutdown();
}
