#pragma once

#include "raylib.h"
#include "TingoBingo/Tingo.h"

class GameWorld
{
public:
    void Initialise();
    void Update(float dt);
    void Draw();
    void Shutdown();

private:
    Camera3D camera{};
    Tingo tingo;
};