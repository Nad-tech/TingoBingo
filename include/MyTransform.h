#pragma once

#include "raylib.h"
#include <cmath>

struct MyTransform
{
    Vector2 position = { 0.0f, 0.0f };
    Vector2 pivot = { 0.0f, 0.0f };
    float rotation = 0.0f;
    float scale = 1.0f;
};

inline MyTransform MakeChildTransform(
    const MyTransform& parentTransform,
    Vector2 positionOffset)
{
    MyTransform child;

    float radians = parentTransform.rotation * DEG2RAD;

    Vector2 rotatedOffset =
    {
        positionOffset.x * cosf(radians) -
        positionOffset.y * sinf(radians),

        positionOffset.x * sinf(radians) +
        positionOffset.y * cosf(radians)
    };

    child.position =
    {
        parentTransform.position.x + rotatedOffset.x,
        parentTransform.position.y + rotatedOffset.y
    };

    child.rotation = parentTransform.rotation;
    child.scale = parentTransform.scale;

    return child;
}