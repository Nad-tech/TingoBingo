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

    /*Shape::SetDimensions(
        dimensions.elbowWidth, 
        dimensions.elbowHeight
    );*/

    foreArm.Initialise();

    positionOffset = {
        0, 0
    };

    pivot = {0, 0};
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
    Shape::transform.pivot = pivot;
    
    foreArm.SetTransform(transform);
}
