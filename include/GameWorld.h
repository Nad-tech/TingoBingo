#pragma once

#include "raylib.h"
#include "TingoBingo/Tingo.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "ScreenDimensions.h"
#include "TingoBingo/TingoState.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/GameObjectAssets.h"
#include <vector>
#include "InputController.h"

class GameWorld
{
public:
    GameWorld(InputController& inputController);
    
    void Initialise(ScreenDimensions& screenDimensions);
    
    void Update(float dt);
    void Draw();
    
    void ShutDown();

    void HandleController(float dt);

private:
    InputController& inputController;
    Camera3D camera{};
    TingoAssets tingoAssets;
    TingoDimensions dimensions;
    Tingo tingo;

    MyTransform3D initialTransform; 
    ScreenDimensions screenDimensions;
    Texture2D spaceBackground{};

    void DrawOrientationGizmo();
    void DrawGesturesStates();

    void HandleInput(float dt);

    GameObjectAssets gameAssets;
    GameObject cube;

    std::vector<GameObject*> worldObjects;
};
