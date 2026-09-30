#include "Sprite.h"
#include <cmath>
#include <iostream>

void Sprite::Draw() const
{    
    Rectangle source = animation.GetSourceRectangle();

    float scale = transform.scale;

    Rectangle destination = {
        screenX - drawGeometry.origin.x * scale,
        screenY - drawGeometry.origin.y * scale,
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
        transform.rotation,
        WHITE
    );
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
