#include "Body/Legs/Thigh.h"
#include "Constants.h"
#include <string>

Thigh::Thigh(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
    Shape(CARDBOARD),
    dimensions(dimensions),
    robotState(robotState),
    side(side),
    knee(dimensions, side, robotState)
{}

void Thigh::Initialise()
{
    dimensions.thighWidth = 80.0f; 
    dimensions.thighHeight = 150.0f;

    drawGeometry.width = dimensions.thighWidth;
    drawGeometry.height = dimensions.thighHeight;

    if(side == "left")
    {
        positionOffset = {
            dimensions.pelvisWidth / 2.0f - 
            dimensions.thighWidth / 2.0f,
            0
        };
    }

    if(side == "right")
    {
        positionOffset = {
            -dimensions.pelvisWidth / 2.0f + 
            dimensions.thighWidth / 2.0f,
            0
        };
    }

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        0
    };

    knee.Initialise();
}

void Thigh::Update(float dt)
{
    Crouch();

    if(crouchState != CrouchState::None)
    {
        AdvanceCrouch(dt);
    }

    knee.Update(dt);
}

void Thigh::Draw() const
{
    Shape::Draw();
    knee.Draw();
}

void Thigh::SetTransform(MyTransform parentTransform)
{
    tempParentTransform = parentTransform;

    transform = MakeChildTransform(parentTransform, positionOffset);
    transform.rotation += localRotation;
    
    SetScreenCoords();

    knee.SetTransform(transform);
}

void Thigh::Crouch()
{
    if(robotState.gestures.crouch && crouchState == CrouchState::None)
    {
        crouchState = CrouchState::Raising;
    }
}

void Thigh::AdvanceCrouch(float dt)
{
    if(side == "left")
    {
        const float speed = 250.0f;
        const float minRotation = 0.0f;
        const float maxRotation = 30.0f;

        if(crouchState == CrouchState::Raising)
        {
            localRotation += speed * dt;
            
            if(localRotation >= maxRotation)
            {
                localRotation = maxRotation;
                crouchState = CrouchState::Crouching;
                //knee.Crouch();
            }
        }
        else if(crouchState == CrouchState::Crouching)
        {
            if(!robotState.gestures.crouch)
            {
                crouchState = CrouchState::Returning;
            }
        }
        else if(crouchState == CrouchState::Returning)
        {
            localRotation -= speed * dt;

            if(localRotation <= minRotation)
            {
                localRotation = minRotation;
                crouchState = CrouchState::None;
            }
        }
    }

    if(side == "right")
    {
        const float speed = 250.0f;
        const float minRotation = 0.0f;
        const float maxRotation = -30.0f;

        if(crouchState == CrouchState::Raising)
        {
            localRotation -= speed * dt;
            
            if(localRotation <= maxRotation)
            {
                localRotation = maxRotation;
                crouchState = CrouchState::Crouching;
                //knee.Crouch();
            }
        }
        else if(crouchState == CrouchState::Crouching)
        {
            if(!robotState.gestures.crouch)
            {
                crouchState = CrouchState::Returning;
            }
        }
        else if(crouchState == CrouchState::Returning)
        {
            localRotation += speed * dt;

            if(localRotation >= minRotation)
            {
                localRotation = minRotation;
                crouchState = CrouchState::None;
            }
        }
    }

    SetTransform(tempParentTransform);
}