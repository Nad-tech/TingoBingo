//====================================================
// Eyes.cpp
//
// Handles the robot's eye sprites and blink animation.
// The eyes are animated independently from the head,
// allowing facial expressions without changing the
// head rotation sprite.
//====================================================

#include "Body/Head/Eyes.h"
#include "Constants.h"
#include <cmath>

Eyes::Eyes(BodyDimensions& dimensions) : 
    dimensions(dimensions),
    pupils(dimensions)
{
}

void Eyes::Initialise()
{
    Sprite::texture = LoadTexture("assets/images/TingoBingo/head/eyes.png");

    const int COLUMNS = 5;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.02f;

    dimensions.eyesWidth = texture.width / COLUMNS;
    dimensions.eyesHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.eyesWidth;
    drawGeometry.height = dimensions.eyesHeight;

    dimensions.eyesYoffset = 30.0f;

    Sprite::animation.Initialise
    (
        dimensions.eyesWidth,
        dimensions.eyesHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0, dimensions.eyesYoffset
    };

    Sprite::drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    pupils.Initialise();
}

void Eyes::Update(float dt, Emotion emotion)
{
    Sprite::Update(dt);

    idleAnimationTimer += dt;
    
    if(idleAnimationTimer > nextIdleAnimation)
    {
        animation.Play(0, 4, AnimationPriority::Idle);
        idleAnimationTimer = 0.0f;
        nextIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }

    pupils.Update(dt, emotion);
}

void Eyes::Draw() const
{
    Sprite::Draw();
    pupils.Draw();
}

void Eyes::SetTransform(MyTransform parentTransform)
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    Sprite::SetScreenCoords();

    pupils.SetTransform(transform);
}

Pupils& Eyes::GetPupils()
{
    return pupils;
}

void Eyes::LookAt(Vector2 point)
{
    pupils.LookAt(point);
}

void Eyes::LookForward()
{
    pupils.LookForward();
}

void Eyes::Shutdown()
{
    UnloadTexture(texture);
    pupils.Shutdown();
}