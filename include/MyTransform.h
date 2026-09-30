#pragma once

#include "raylib.h"
#include <cmath>

struct MyTransform
{
    Vector2 position = { 0.0f, 0.0f };
    Vector2 globalPivot = { 0.0f, 0.0f };
    Vector2 joint = { 0.0f, 0.0f };
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

inline Vector2 RotateVector(MyTransform& transform, Vector2 joint) 
{
    float radians = transform.rotation * DEG2RAD;

    return {
        joint.x * cosf(radians) - joint.y * sinf(radians),
        joint.x * sinf(radians) + joint.y * cosf(radians)
    };
}

inline Vector2 AddVector(Vector2 a, Vector2 b)
{
    return {
        a.x + b.x,
        a.y + b.y
    };
}