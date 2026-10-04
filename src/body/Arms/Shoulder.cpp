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
    if(shrugState != ShrugState::None)
    {
        AdvanceShrug(dt);
    }

    upperArm.Update(dt);
}

void Shoulder::Draw() const 
{
    upperArm.Draw();
    Shape::Draw();   
}

void Shoulder::SetTransform(MyTransform parentTransform)
{
    tempParentTransform = parentTransform;
    
    transform = MakeChildTransform(parentTransform, positionOffset);
    transform.position.y += shrugOffsetY;

    Shape::SetScreenCoords();

    upperArm.SetTransform(transform);
}

void Shoulder::Wave()
{
    upperArm.Wave();
}

void Shoulder::Shrug()
{
    if(shrugState == ShrugState::None)
    {
        shrugState = ShrugState::Raising;
    }
}

void Shoulder::AdvanceShrug(float dt)
{
    const float speed = 250.0f;
    const float minOffset = 0.0f;
    const float maxOffset = 30.0f;

    if(shrugState == ShrugState::Raising)
    {
        shrugOffsetY += speed * dt;
        
        if(shrugOffsetY >= maxOffset)
        {
            shrugOffsetY = maxOffset;
            shrugState = ShrugState::Shrugging;
            upperArm.Shrug();
        }
    }
    else if(shrugState == ShrugState::Shrugging)
    {
        if(!robotState.gestures.shrug)
        {
            shrugState = ShrugState::Lowering;
        }
    }
    else if(shrugState == ShrugState::Lowering)
    {
        shrugOffsetY -= speed * dt;

        if(shrugOffsetY <= minOffset)
        {
            shrugOffsetY = minOffset;
            shrugState = ShrugState::None;
        }
    }
    

    SetTransform(tempParentTransform);
}