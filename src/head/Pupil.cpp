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
    dimensions.pupilWidth = 100;
    dimensions.pupilHeight = 100;

    if(side == "left") {
        positionOffset = {sideOffset, 0};
    }

    if(side == "right")
    {
        positionOffset = {-sideOffset, 0};
    }
    
}

// Advance the pupil animation.
void Pupil::Update(float dt)
{

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
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
}