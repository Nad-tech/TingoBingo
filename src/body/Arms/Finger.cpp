#include "Body\Arms\Finger.h"
#include <iostream>

Finger::Finger
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& robotState
) : 
    Shape(CARDBOARD_LIGHT),
    dimensions(dimensions),
    robotState(robotState),
    side(side)
{}
        
void Finger::Initialise()
{
    dimensions.fingerWidth = 15.0f;
    dimensions.fingerHeight = 50.0f;

    drawGeometry.width = dimensions.fingerWidth;
    drawGeometry.height = dimensions.fingerHeight;

    
    if(side == "left")
    {
        positionOffset = {
            -dimensions.handWidth / 2.0f + dimensions.fingerWidth / 2.0f,
            -dimensions.handHeight / 2.0f + 10.0f
        };
    }

    if(side == "right")
    {
        positionOffset = {
            dimensions.handWidth / 2.0f - dimensions.fingerWidth / 2.0f,
            -dimensions.handHeight / 2.0f + 10.0f
        };
    }

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        0.0f
    };
}
        
void Finger::Update(float dt)
{
    AdvanceOpenClose(dt);
}

void Finger::Draw() const
{
    Shape::Draw();
}
        
void Finger::SetTransform(MyTransform parentTransform)
{
    tempParentTransform = parentTransform;
    transform = MakeChildTransform(parentTransform, positionOffset);
    transform.rotation += side == "left" ? localRotation : -localRotation;
    SetScreenCoords();
}

void Finger::Open()
{
    state = FingerState::Open;
}

void Finger::Close()
{
    state = FingerState::Close;
}

void Finger::AdvanceOpenClose(float dt)
{
    float speed = 100.0f;
    float max = 25.0f;
    float min = 0.0f;

    if(state == FingerState::Open)
    {
        localRotation -= dt * speed;
        
        if(localRotation <= min)
        {
            localRotation = min;
            return;
        }
    }

    if(state == FingerState::Close)
    {
        localRotation += dt * speed;

        if(localRotation >= max)
        {
            localRotation = max;
            return;
        }
    }

    SetTransform(tempParentTransform);
}