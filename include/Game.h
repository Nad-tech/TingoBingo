#pragma once

#include "GameWorld.h"

class Game
{
public:
    void Initialise();
    void Run();
    void Shutdown();

private:
    GameWorld world;
};