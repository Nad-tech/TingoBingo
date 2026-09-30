#pragma once

#include "raylib.h"

struct DrawGeometry
{
    // Drawable width in local pixels before scaling.
    float width = 0.0f;

    // Drawable height in local pixels before scaling.
    float height = 0.0f;

    // Local pixel position of the transform pivot measured from the
    // drawable's top-left corner, using Raylib's screen-space origin rules.
    Vector2 origin = {0.0f, 0.0f};
};