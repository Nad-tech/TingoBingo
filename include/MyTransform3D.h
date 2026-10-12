#pragma once

#include "raylib.h"

struct MyTransform3D 
{
    Vector3 position = {0.0f, 0.0f, 0.0f};
    Vector3 rotation = {0.0f, 0.0f, 0.0f};
    Vector3 scale = {0.0f, 0.0f, 0.0f};
};

inline MyTransform3D MakeChildTransform
(
    const MyTransform3D& parentTransform,
    Vector3 positionOffset
)
{
    MyTransform3D child;

    (void)parentTransform;
    (void)positionOffset;

    return child;
}