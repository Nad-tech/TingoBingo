#pragma once

#include "raylib.h"
#include "GameObjects/GameObject.h"

#include <vector>

class TingoVision
{
public:
    void Initialise();

    void Update(
        Vector3 observerPosition,
        const std::vector<GameObject*>& objects
    );

    const std::vector<GameObject*>& GetVisibleObjects() const;

    void Draw();

private:
    Vector3 observerPosition;
    float visionRange;
    float visionFOV;

    std::vector<GameObject*> visibleObjects;

    bool IsWithinRange(
        Vector3 observerPosition,
        BoundingBox bounds
    ) const;

    Vector3 forwardDirection = { 0.0f, 0.0f, 1.0f };

    bool IsWithinFieldOfView(
        Vector3 observerPosition, 
        Vector3 targetPosition
    ) const;

    void DrawVisionCone() const;
};