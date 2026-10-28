#pragma once

#include "raylib.h"
#include "TingoBingo/Tingo.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "ScreenDimensions.h"
#include "TingoBingo/TingoState.h"
#include "DebugPanel.h"
#include "GameObjects/GameObject.h"

class GameWorld
{
public:
    GameWorld();
    
    void Initialise(ScreenDimensions& screenDimensions);
    
    void Update(float dt);
    void Draw();
    
    void Shutdown();

private:
    Camera3D camera{};
    TingoAssets assets;
    TingoDimensions dimensions;
    Tingo tingo;

    MyTransform3D initialTransform; 
    ScreenDimensions screenDimensions;
    Texture2D spaceBackground{};

    void DrawOrientationGizmo();
    void DrawGesturesStates();

    void HandleInput(float dt);

    GameObject object;
};