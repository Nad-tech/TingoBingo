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

    if(side == "left") {Shape::SetShapeName("leftUpperArm");}
    if(side == "right") {Shape::SetShapeName("rightUpperArm");}
}

void UpperArm::Update(float dt)
{
    if(waveState != WaveState::None)
    {
        WaveArm(dt);
    }

    elbow.Update(dt);
}


// Draw the upper arm.
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

void UpperArm::Wave()
{
    if(waveState == WaveState::None)
    {
        waveState = WaveState::Raising;
    }
}

void UpperArm::WaveArm(float dt)
{
    const float speed = 100.0f;
    const float maxRotation = -60.0f;

    if(waveState == WaveState::Raising)
    {
        localRotation -= speed * dt;

        if(localRotation <= maxRotation)
        {
            localRotation = maxRotation;
            elbow.SetWaveState(Elbow::WaveState::Waving);
        }
    }
    else if(waveState == WaveState::Lowering)
    {
        elbow.SetWaveState(Elbow::WaveState::None);

        localRotation += speed * dt;

        if(localRotation >= 0.0f)
        {
            localRotation = 0.0f;
            waveState = WaveState::None;
        }
    }

    SetTransform(tempParentTransform);
}