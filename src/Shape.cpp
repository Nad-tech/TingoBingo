

#include "Shape.h"
#include <cmath>

void Shape::Draw() const
{
    // Convert Cartesian world position to Raylib screen coordinates.
    Vector2 screenPosition =
    {
        SCREEN_WIDTH / 2.0f + transform.position.x * transform.scale,
        SCREEN_HEIGHT / 2.0f - transform.position.y * transform.scale
    };

    // Scale the shape dimensions.
    float scaledWidth = width * transform.scale;
    float scaledHeight = height * transform.scale;

    // Position the rectangle so that transform.position
    // represents the CENTRE of the shape.
    Rectangle rectangle =
    {
        screenPosition.x - scaledWidth / 2.0f,
        screenPosition.y - scaledHeight / 2.0f,
        scaledWidth,
        scaledHeight
    };

    // Convert the Cartesian pivot offset into screen coordinates.
    //
    // pivot is the vector from:
    //
    //     child centre -> rotation joint
    //
    // Cartesian +Y points upward, while screen +Y points downward,
    // so the Y component must be inverted.
    Vector2 origin =
    {
        scaledWidth / 2.0f + transform.pivot.x * transform.scale,
        scaledHeight / 2.0f - transform.pivot.y * transform.scale
    };

    DrawRectanglePro(
        rectangle,
        origin,
        -transform.rotation,
        color
    );
}

void Shape::SetDimensions(float width, float height)
{
    this->width = width;
    this->height = height;
}

void Shape::Shutdown()
{
    
}

void Shape::SetTransform(MyTransform transform)
{
    this->transform = transform;
}
