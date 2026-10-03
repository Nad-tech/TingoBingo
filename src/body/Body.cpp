#include "Body/Body.h"
#include <cmath>

Body::Body(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    bodyBase(dimensions),
    neck(dimensions, robotState),
    pelvis(dimensions, robotState),
    arms(dimensions, robotState)
{}

void Body::Initialise()
{
    bodyBase.Initialise();
    neck.Initialise();
    arms.Initialise();
    pelvis.Initialise();
}

void Body::Shutdown()
{
    neck.Shutdown();
    arms.Shutdown();
    pelvis.Shutdown();
}

void Body::Update(float dt)
{
    Crouch();

    if(crouchState != CrouchState::None)
    {
        AdvanceCrouch(dt);
    }

    neck.Update(dt);
    arms.Update(dt);
    pelvis.Update(dt);
}

void Body::Draw() const
{
    bodyBase.Draw();
    arms.Draw();
    neck.Draw();
    pelvis.Draw();
}

void Body::SetTransform(MyTransform parentTransform)
{
    transform = parentTransform;
    tempParentTransform = parentTransform;

    transform.position.y += crouchOffsetY;

    bodyBase.SetTransform(this->transform);
    neck.SetTransform(this->transform);
    arms.SetTransform(this->transform);
    pelvis.SetTransform(this->transform);
}

void Body::Crouch()
{
    if(robotState.gestures.crouch && crouchState == CrouchState::None)
    {
        crouchState = CrouchState::Lowering;
    }
}

void Body::AdvanceCrouch(float dt)
{
    const float speed = 250.0f;
    const float minOffset = -30.0f;

    if(crouchState == CrouchState::Lowering)
    {
        crouchOffsetY -= speed * dt;

        if(crouchOffsetY <= minOffset)
        {
            crouchOffsetY = minOffset;

            pelvis.Crouch();
        
            if(!robotState.gestures.crouch)
            {
                crouchState = CrouchState::Returning;
            }
            
        }
    }
    else if(crouchState == CrouchState::Returning)
    {
        if(crouchOffsetY < 0.0f)
        {
            crouchOffsetY += speed * dt;

            if(crouchOffsetY >= 0.0f)
            {
                crouchOffsetY = 0.0f;
                crouchState = CrouchState::None;
            }
        }
        else
        {
            crouchState = CrouchState::None;
        }
    }

    SetTransform(tempParentTransform);
}