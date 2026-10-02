#include "Body/Arms/Shoulder.h"
#include "Constants.h"
#include <cmath>
#include <iostream>
#include "raymath.h"

Shoulder::Shoulder
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& robotState
) :
    Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    robotState(robotState),
    side(side),
    upperArm(dimensions, side, robotState)
{
}

void Shoulder::Initialise()
{
    dimensions.shoulderWidth = 65.0f;
    dimensions.shoulderHeight = 65.0f;

    drawGeometry.width = dimensions.shoulderWidth;
    drawGeometry.height = dimensions.shoulderHeight;

    if(side == "left") 
    {
        positionOffset = {
            dimensions.bodyWidth / 2.0f + dimensions.shoulderWidth / 2.0f,
            dimensions.bodyHeight / 2.0f - dimensions.shoulderHeight / 2.0f
        };

        Shape::SetShapeName("leftShoulder");
    }

    if(side == "right") 
    {
        positionOffset = {
            -dimensions.bodyWidth / 2.0f - dimensions.shoulderWidth / 2.0f,
            dimensions.bodyHeight / 2.0f - dimensions.shoulderHeight / 2.0f
        };
    }

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    upperArm.Initialise();
}

// Update the shoulder and its child upper arm.
void Shoulder::Update(float dt)
{
    upperArm.Update(dt);
}

void Shoulder::Draw() const 
{
    upperArm.Draw();
    Shape::Draw();   
}

void Shoulder::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);

    Shape::SetScreenCoords();

    upperArm.SetTransform(transform);
}