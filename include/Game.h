#pragma once

#include "GameWorld.h"
#include "ScreenDimensions.h"
#include "InputController.h"

class Game
{
public:
    Game();
    void Initialise();
    void Run();
    void Shutdown();

private:
    InputController inputController;
    GameWorld world;
    ScreenDimensions screenDimensions;
    
    void DrawLegend();
};