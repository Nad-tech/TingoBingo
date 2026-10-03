#include "Body/Legs/Shin.h"

Shin::Shin(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
	Shape(CARDBOARD),
	dimensions(dimensions),
    robotState(robotState),
	side(side),
    foot(dimensions, side, robotState)
{}

void Shin::Initialise()
{
    dimensions.shinWidth = 70.0f; 
    dimensions.shinHeight = 150.0f;

    drawGeometry.width = dimensions.shinWidth;
    drawGeometry.height = dimensions.shinHeight;

    if(side == "left")
    {
        positionOffset = {
            0,
            0
        };
    }

    if(side == "right")
    {
        positionOffset = {
			0,
            0
        };
    }

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        0
    };

	foot.Initialise();
}

void Shin::Update(float dt)
{
    Crouch();

    if(crouchState != CrouchState::None)
    {   
        AdvanceCrouch(dt);
    }

    foot.Update(dt);
}

void Shin::Draw() const
{
    Shape::Draw();
	foot.Draw();
}

void Shin::SetTransform(MyTransform parentTransform)
{
    tempParentTransform = parentTransform;

    transform = MakeChildTransform(parentTransform, positionOffset);
    transform.rotation += localRotation;

    SetScreenCoords();

	foot.SetTransform(Shape::transform);
}

void Shin::Crouch()
{
    if(robotState.gestures.crouch && crouchState == CrouchState::None)
    {
        crouchState = CrouchState::Raising;
    }
}

void Shin::AdvanceCrouch(float dt)
{
    if(side == "left")
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
                //foot.Crouch();
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

    if(side == "right")
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

    SetTransform(tempParentTransform);
}