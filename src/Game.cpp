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

	if (IsKeyPressed(KEY_ONE)) robot.ToggleGesture(RobotState::Gesture::Idle);
	if (IsKeyPressed(KEY_TWO)) robot.ToggleGesture(RobotState::Gesture::Nod);
	if (IsKeyPressed(KEY_THREE)) robot.ToggleGesture(RobotState::Gesture::ShakeHead);
	if (IsKeyPressed(KEY_FOUR)) robot.ToggleGesture(RobotState::Gesture::WaveLeft);
	if (IsKeyPressed(KEY_FIVE)) robot.ToggleGesture(RobotState::Gesture::WaveRight);
	if (IsKeyPressed(KEY_SIX)) robot.ToggleGesture(RobotState::Gesture::Shrug);
	if (IsKeyPressed(KEY_EIGHT)) robot.ToggleGesture(RobotState::Gesture::Celebrate);
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
