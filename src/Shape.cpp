#include "Shape.h"
#include <cmath>
#include <iostream>

void Shape::Draw() const
{    
    float scale = transform.scale;

    Rectangle rectangle = {
        screenX,
        screenY,
        drawGeometry.width * scale,
        drawGeometry.height * scale
    };

    DrawRectanglePro(
        rectangle,
        {
            drawGeometry.origin.x * scale,
            drawGeometry.origin.y * scale
        },
        -transform.rotation,
        color
    );
}

void Shape::SetScreenCoords()
{
    float scale = transform.scale;

    screenX = SCREEN_WIDTH / 2.0f + transform.position.x * scale;
    screenY = SCREEN_HEIGHT / 2.0f - transform.position.y * scale;
}

void Shape::SetShapeName(std::string name) 
{
    this->name = name;
}