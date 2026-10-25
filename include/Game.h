#pragma once

#include "GameWorld.h"
#include "ScreenDimensions.h"

class Game
{
public:
    void Initialise();
    void Run();
    void Shutdown();

private:
    GameWorld world;
    ScreenDimensions screenDimensions;
    
    void DrawLegend();
};