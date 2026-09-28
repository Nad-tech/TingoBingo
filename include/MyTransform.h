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

    // ------------------------------------------------------------
    // 1. Rotate the parent's pivot offset into world space.
    //
    // parentTransform.pivot is stored as:
    //
    //     parent centre -> parent rotation joint
    //
    // Because the parent can rotate, that offset must rotate
    // with the parent.
    // ------------------------------------------------------------

    Vector2 rotatedParentPivot =
    {
        parentTransform.pivot.x * cosf(radians) -
        parentTransform.pivot.y * sinf(radians),

        parentTransform.pivot.x * sinf(radians) +
        parentTransform.pivot.y * cosf(radians)
    };


    // ------------------------------------------------------------
    // 2. Find the parent's rotation joint in world space.
    // ------------------------------------------------------------

    Vector2 parentJointPosition =
    {
        parentTransform.position.x + rotatedParentPivot.x,
        parentTransform.position.y + rotatedParentPivot.y
    };


    // ------------------------------------------------------------
    // 3. Rotate the child's position offset with the parent.
    //
    // positionOffset describes:
    //
    //     parent joint -> child centre
    //
    // so it must follow the parent's rotation.
    // ------------------------------------------------------------

    Vector2 rotatedPositionOffset =
    {
        positionOffset.x * cosf(radians) -
        positionOffset.y * sinf(radians),

        positionOffset.x * sinf(radians) +
        positionOffset.y * cosf(radians)
    };


    // ------------------------------------------------------------
    // 4. Calculate the child's centre position.
    // ------------------------------------------------------------

    child.position =
    {
        parentJointPosition.x + rotatedPositionOffset.x,
        parentJointPosition.y + rotatedPositionOffset.y
    };


    // ------------------------------------------------------------
    // 5. The child's pivot is the vector from:
    //
    //     child centre -> parent joint
    //
    // positionOffset points:
    //
    //     parent joint -> child centre
    //
    // so negate it.
    //
    // Because this is stored in the child's local coordinate
    // system, we don't need the rotated version here.
    // ------------------------------------------------------------

    child.pivot =
    {
        -positionOffset.x,
        -positionOffset.y
    };


    // ------------------------------------------------------------
    // 6. Inherit rotation and scale.
    // ------------------------------------------------------------

    child.rotation = parentTransform.rotation;
    child.scale = parentTransform.scale;


    return child;
}