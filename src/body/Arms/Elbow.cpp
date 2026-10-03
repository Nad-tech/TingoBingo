#include "Body/Arms/Elbow.h"
#include <cmath>
#include <iostream>

Elbow::Elbow
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& robotState
) :
    Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    robotState(robotState),
    side(side),
    foreArm(dimensions, side, robotState)
{}

void Elbow::Initialise()
{
    dimensions.elbowWidth = 65.0f;
    dimensions.elbowHeight = 65.0f;

    drawGeometry.width = dimensions.elbowWidth;
    drawGeometry.height = dimensions.elbowHeight;

    positionOffset = {
        0, 
        -dimensions.upperArmHeight
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
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

void Elbow::WaveArm()
{
    foreArm.WaveArm();
}