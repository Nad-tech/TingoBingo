#include "Shape.h"
#include <cmath>
#include <iostream>

void Shape::Draw() const
{    
    float scale = transform.scale;

    if(hasJoint)
    {
        Rectangle rec = {
            screenX,
            screenY,
            width * scale,
            height * scale
        };

        Vector2 screenPivot = {
            (width * scale / 2.0f) +
                transform.joint.x * scale,

            (height * scale / 2.0f) -
                transform.joint.y * scale
        };

        DrawRectanglePro(
            rec,
            screenPivot,
            -transform.rotation,
            color
        );
    }
    else
    {
        Rectangle rec = {
            screenX + transform.globalPivot.x * scale,
            screenY - transform.globalPivot.y * scale,
            width * transform.scale,
            height * transform.scale
        };
        
        Vector2 screenPivot = {
            (width * scale / 2.0f) + transform.globalPivot.x * scale,
            (height * scale / 2.0f) - transform.globalPivot.y * scale
        };

        DrawRectanglePro(
            rec,
            screenPivot,
            -transform.rotation,
            color  
        );
    }

    //DebugDraw();
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
                transform.globalPivot.x,
                transform.globalPivot.y,
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

    if(name == "headBase")
    {
        DrawText(
            TextFormat
            (   
                "headBase: "
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
                transform.globalPivot.x,
                transform.globalPivot.y,
                transform.rotation,
                transform.scale,
                width,
                height
            ),
            0,
            40,
            20,
            WHITE
        );
    }
}
