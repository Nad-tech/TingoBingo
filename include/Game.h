#pragma once

#include "Robot.h"
#include "Input.h"
#include "BodyDimensions.h"
class Game
{
public:
	void Run();
	
private:
	void Initialise();
	void Shutdown();

	void HandleInput();
	void Update(const float dt);
	void Draw();
	
	Robot robot;
	Vector2 robotWorldPos;
	Input input;
	Texture2D background;
};