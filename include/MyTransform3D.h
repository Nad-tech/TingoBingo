#pragma once

#include "raylib.h"
#include "raymath.h"

struct MyTransform3D
{
    Vector3 position = { 0.0f, 0.0f, 0.0f };

    // Axis around which the model rotates.
    Vector3 rotationAxis = { 0.0f, 0.0f, 0.0f };

    // Rotation angle in degrees.
    float rotationAngle = 0.0f;

    // Scale along the X, Y and Z axes.
    Vector3 scale = { 1.0f, 1.0f, 1.0f };
};

inline MyTransform3D MakeChildTransform(
    const MyTransform3D& parent,
    const MyTransform3D& child)
{
    MyTransform3D result{};

    // 1. Scale the child's local position.
    Vector3 scaledOffset = Vector3Multiply(
        child.position,
        parent.scale
    );

    // 2. Convert the parent's rotation to a quaternion.
    Quaternion parentRotation = QuaternionFromAxisAngle(
        parent.rotationAxis,
        parent.rotationAngle * DEG2RAD
    );

    // 3. Rotate the child's offset around the parent.
    Vector3 rotatedOffset = Vector3RotateByQuaternion(
        scaledOffset,
        parentRotation
    );

    // 4. Calculate the child's world position.
    result.position = Vector3Add(
        parent.position,
        rotatedOffset
    );

    // 5. Combine rotations.
    Quaternion childRotation = QuaternionFromAxisAngle(
        child.rotationAxis,
        child.rotationAngle * DEG2RAD
    );

    Quaternion combinedRotation = QuaternionMultiply(
        parentRotation,
        childRotation
    );

    // 6. Convert the combined rotation back to axis-angle.
    Vector3 axis;
    float angle;

    QuaternionToAxisAngle(
        combinedRotation,
        &axis,
        &angle
    );

    result.rotationAxis = axis;
    result.rotationAngle = angle * RAD2DEG;

    // 7. Combine scales.
    result.scale = Vector3Multiply(
        parent.scale,
        child.scale
    );

    return result;
}