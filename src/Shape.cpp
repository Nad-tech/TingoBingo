#include "Shape.h"
#include <cmath>
#include <iostream>

void Shape::Draw() const
{    
    float scale = transform.scale;

    Rectangle rec = {
        screenX + transform.pivot.x * scale,
        screenY - transform.pivot.y * scale,
        width * transform.scale,
        height * transform.scale
    };
    
    Vector2 screenPivot = {
        (width * scale / 2.0f) + transform.pivot.x * scale,
        (height * scale / 2.0f) - transform.pivot.y * scale
    };

    DrawRectanglePro(
        rec,
        screenPivot,
        -transform.rotation,
        color  
    );

    DebugDraw();
}

void Shape::SetScreenCoords()
{
    float scale = transform.scale;

    screenX = SCREEN_WIDTH / 2.0f + transform.position.x * scale;
    screenY = SCREEN_HEIGHT / 2.0f - transform.position.y * scale;
}

void Shape::SetDimensions(float w, float h)
{
    width = w;
    height = h;
}

void Shape::SetShapeName(std::string name) 
{
    this->name = name;
}

void Shape::DebugDraw() const
{
    if(name == "bodyBase")
    {
        DrawText(
            TextFormat
            (   
                "bodyBase: "
                "pos(%.1f,%.1f)," 
                "spos(%.1f,%.1f)," 
                "piv(%.1f,%.1f)," 
                "rot(%.1f),"
                "sca:(%.1f),"
                "W(%.1f) H(%.1f)",
                transform.position.x,
                transform.position.y,
                screenX,
                screenY,
                transform.pivot.x,
                transform.pivot.y,
                transform.rotation,
                transform.scale,
                width,
                height
            ),
            0,
            0,
            20,
            WHITE
        );
    }

    if(name == "neck")
    {
        DrawText(
            TextFormat
            (   
                "neck: "
                "pos(%.1f,%.1f)," 
                "spos(%.1f,%.1f)," 
                "piv(%.1f,%.1f)," 
                "rot(%.1f),"
                "sca:(%.1f),"
                "W(%.1f) H(%.1f)",
                transform.position.x,
                transform.position.y,
                screenX,
                screenY,
                transform.pivot.x,
                transform.pivot.y,
                transform.rotation,
                transform.scale,
                width,
                height
            ),
            0,
            20,
            20,
            WHITE
        );
    }
}
