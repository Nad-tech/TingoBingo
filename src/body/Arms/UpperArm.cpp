#include "Body/Arms/UpperArm.h"
#include "Constants.h"
#include "raylib.h"
#include <cmath>
#include <iostream>
#include <string>

// Construct the upper arm using the shared body dimensions
// and the side of the body that the arm belongs to.
UpperArm::UpperArm
(
    BodyDimensions& dimensions, 
    std::string side, 
    RobotState& robotState
) :
    Shape(CARDBOARD_LIGHT),
    dimensions(dimensions),
    robotState(robotState),
    side(side),
    elbow(dimensions, side, robotState)
{
}

// Initialise the upper arm and its animation.
void UpperArm::Initialise()
{
    dimensions.upperArmWidth = 50.0f;
    dimensions.upperArmHeight = 120.0f;

    drawGeometry.width = dimensions.upperArmWidth;
    drawGeometry.height = dimensions.upperArmHeight;

    positionOffset = {
        0, 
        0
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        0
    };

    elbow.Initialise();
}

void UpperArm::Update(float dt)
{
    if(waveState != WaveState::None)
    {
        AdvanceWave(dt);
    }

    elbow.Update(dt);
}

void UpperArm::Draw() const
{
    Shape::Draw();
    elbow.Draw();
}

void UpperArm::SetTransform(MyTransform parentTransform)
{   
    tempParentTransform = parentTransform;

    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::transform.rotation += localRotation;

    Shape::SetScreenCoords();

    elbow.SetTransform(Shape::transform);
}

void UpperArm::WaveArm()
{
    if(waveState == WaveState::None)
    {
        waveState = WaveState::Raising;
    }
}

void UpperArm::AdvanceWave(float dt)
{
    if(side == "left")
    {
        const float speed = 250.0f;
        const float minRotation = 0.0f;
        const float maxRotation = 120.0f;

        if(waveState == WaveState::Raising)
        {
            localRotation += speed * dt;
            
            if(localRotation >= maxRotation)
            {
                localRotation = maxRotation;
                waveState = WaveState::Waving;
                elbow.WaveArm();
            }
        }
        else if(waveState == WaveState::Waving)
        {
            if(!robotState.gestures.waveLeft)
            {
                waveState = WaveState::Lowering;
            }
        }
        else if(waveState == WaveState::Lowering)
        {
            localRotation -= speed * dt;

            if(localRotation <= minRotation)
            {
                localRotation = minRotation;
                waveState = WaveState::None;
            }
        }
    }

    if(side == "right")
    {
        const float speed = 250.0f;
        const float minRotation = 0.0f;
        const float maxRotation = -120.0f;

        if(waveState == WaveState::Raising)
        {
            localRotation -= speed * dt;
            
            if(localRotation <= maxRotation)
            {
                localRotation = maxRotation;
                waveState = WaveState::Waving;
                elbow.WaveArm();
            }
        }
        else if(waveState == WaveState::Waving)
        {
            if(!robotState.gestures.waveRight)
            {
                waveState = WaveState::Lowering;
            }
        }
        else if(waveState == WaveState::Lowering)
        {
            localRotation += speed * dt;

            if(localRotation >= minRotation)
            {
                localRotation = minRotation;
                waveState = WaveState::None;
            }
        }
    }

    SetTransform(tempParentTransform);
}