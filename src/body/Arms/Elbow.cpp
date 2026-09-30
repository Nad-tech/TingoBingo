#include "Body/Arms/Elbow.h"
#include <cmath>
#include <iostream>

Elbow::Elbow(BodyDimensions& dimensions, std::string side) :
    Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    side(side),
    foreArm(dimensions, side)
{}

void Elbow::Initialise()
{
    dimensions.elbowWidth = 65.0f;
    dimensions.elbowHeight = 65.0f;

    positionOffset = {
        0, 
        -dimensions.upperArmHeight / 2.0f
    };

    foreArm.Initialise();
}

void Elbow::Update(float dt)
{
    foreArm.Update(dt);
}

void Elbow::Draw() const 
{
    foreArm.Draw();
    Shape::Draw();
}

void Elbow::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    
    Shape::SetScreenCoords();
    
    foreArm.SetTransform(transform);
}
