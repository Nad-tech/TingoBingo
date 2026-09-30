#include "Sprite.h"
#include <cmath>
#include <iostream>

void Sprite::Draw() const
{    
    Rectangle source = animation.GetSourceRectangle();

    float scale = transform.scale;

    Rectangle destination = {
        screenX,
        screenY,
        drawGeometry.width * scale,
        drawGeometry.height * scale
    };

    DrawTexturePro(
        texture,
        source,
        destination,
        {
            drawGeometry.origin.x * scale,
            drawGeometry.origin.y * scale
        },
        -transform.rotation,
        WHITE
    );

    //DebugDraw();
}

void Sprite::Update(float dt) 
{
    animation.Update(dt);
}

void Sprite::SetScreenCoords()
{
    float scale = transform.scale;

    screenX = SCREEN_WIDTH / 2.0f + transform.position.x * scale;
    screenY = SCREEN_HEIGHT / 2.0f - transform.position.y * scale;
}

void Sprite::SetShapeName(std::string name) 
{
    this->name = name;
}

void Sprite::Shutdown()
{
    UnloadTexture(texture);
}

void Sprite::DebugDraw() const
{
    if(name != "bodyBase")
    {
        return;
    }

    float scale = transform.scale;
    float destinationX = screenX - drawGeometry.origin.x * scale;
    float destinationY = screenY - drawGeometry.origin.y * scale;
    float destinationWidth = drawGeometry.width * scale;
    float destinationHeight = drawGeometry.height * scale;
    float raylibOriginX = drawGeometry.origin.x * scale;
    float raylibOriginY = drawGeometry.origin.y * scale;

    DrawText(
        TextFormat(
            "bodyBase "
            "cart(%.1f, %.1f) "
            "screen(%.1f, %.1f) "
            "size(%.1f, %.1f) "
            "origin(%.1f, %.1f) "
            "dest(%.1f, %.1f)",
            transform.position.x,
            transform.position.y,
            screenX,
            screenY,
            drawGeometry.width,
            drawGeometry.height,
            raylibOriginX,
            raylibOriginY,
            destinationX,
            destinationY
        ),
        10,
        20,
        18,
        WHITE
    );

    DrawRectangleLines(
        (int)destinationX,
        (int)destinationY,
        (int)destinationWidth,
        (int)destinationHeight,
        YELLOW
    );

    DrawCircle(
        (int)screenX,
        (int)screenY,
        7.0f,
        RED
    );
}

