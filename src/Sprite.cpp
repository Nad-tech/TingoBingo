#include "Sprite.h"
#include <cmath>
#include <iostream>

void Sprite::Draw() const
{    
    Rectangle source = animation.GetSourceRectangle();

    float scale = transform.scale;

    Rectangle destination = {
        screenX + transform.globalPivot.x * scale,
        screenY - transform.globalPivot.y * scale,
        width * transform.scale,
        height * transform.scale
    };
    
    Vector2 screenPivot = {
        (width * scale / 2.0f) + transform.globalPivot.x * scale,
        (height * scale / 2.0f) - transform.globalPivot.y * scale
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        screenPivot,
        -transform.rotation,
        WHITE
    );    

    //DebugDraw();
}

void Sprite::SetScreenCoords()
{
    float scale = transform.scale;

    screenX = SCREEN_WIDTH / 2.0f + transform.position.x * scale;
    screenY = SCREEN_HEIGHT / 2.0f - transform.position.y * scale;
}

void Sprite::SetDimensions(float w, float h)
{
    width = w;
    height = h;
}

void Sprite::SetShapeName(std::string name) 
{
    this->name = name;
}

void Sprite::DebugDraw() const
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
                transform.globalPivot.x,
                transform.globalPivot.y,
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

void Sprite::Update(float dt)
{
    animation.Update(dt);
}

void Sprite::Shutdown()
{
    UnloadTexture(texture);
}
