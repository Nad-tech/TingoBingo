//====================================================
// Pupil.cpp
//
// Handles the robot's pupil sprite.
//
// The pupil is drawn separately from the eyes so it
// can move independently when the robot looks around.
//====================================================

#include "Body/Head/Pupil.h"
#include "Constants.h"
#include <cmath>
#include <string>

Pupil::Pupil(BodyDimensions& dimensions) :
    dimensions(dimensions)
{}

// Load the pupil sprite and initialise its animation.
void Pupil::Initialise()
{
    Sprite::texture = LoadTexture("assets/images/TingoBingo/head/pupil.png");

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.08f;

    dimensions.pupilWidth = texture.width / COLUMNS;
    dimensions.pupilHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.pupilWidth;
    drawGeometry.height = dimensions.pupilHeight;

    animation.Initialise
    (
        dimensions.pupilWidth,
        dimensions.pupilHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    if(side == "left") {
        positionOffset = {sideOffset, 0};
    }

    if(side == "right")
    {
        positionOffset = {-sideOffset, 0};
    }
    
    Sprite::drawGeometry.origin = {
        dimensions.pupilWidth / 2.0f,
        dimensions.pupilHeight / 2.0f
    };
}

// Advance the pupil animation.
void Pupil::Update(float dt, Emotion emotion)
{
    Sprite::Update(dt);
}

void Pupil::SetSide(std::string side)
{
    this->side = side;
}

float Pupil::GetSideOffset()
{
    return sideOffset;
}

void Pupil::SetPosition(Vector2 position)
{
    float radians = transform.rotation * DEG2RAD;
    float X = positionOffset.x;
    float Y = positionOffset.y;

    transform.position = {
            position.x + X * cosf(radians) - Y * sinf(radians),
            position.y + X * sinf(radians) + Y * cosf(radians)
    };
}

void Pupil::SetRotation(float rotation)
{
    transform.rotation = rotation;
}

void Pupil::SetTransform(MyTransform parentTransform) 
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    Sprite::SetScreenCoords();
}