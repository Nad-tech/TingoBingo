#pragma once

#include "raylib.h"
#include "Vector4Int.h"

class GameObjectAssets {
public:
    void Initialise();
    void ShutDown();

    Vector3 GetCubeDimensions();
    
    Model cube{};
    
    // Shared lighting shader.
    Shader lightingShader{};

    // Shader uniform locations.
    int lightDirectionLoc = -1;
    int ambientLoc = -1;
    int viewPositionLoc = -1;

    // Update the lighting using the current camera position.
    void UpdateLighting(Vector3 cameraPosition);
};