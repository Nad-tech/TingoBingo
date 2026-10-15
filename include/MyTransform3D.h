#pragma once

#include "raylib.h"

struct MyTransform3D
{
    Vector3 position = { 0.0f, 0.0f, 0.0f };

    // Axis around which the model rotates.
    Vector3 rotationAxis = { 0.0f, 1.0f, 0.0f };

    // Rotation angle in degrees.
    float rotationAngle = 0.0f;

    // Scale along the X, Y and Z axes.
    Vector3 scale = { 1.0f, 1.0f, 1.0f };
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