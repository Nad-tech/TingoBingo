#include "Body/Arms/ForeArm.h"

ForeArm::ForeArm
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& robotState
) :
	Shape(CARDBOARD_LIGHT),
    dimensions(dimensions),
    robotState(robotState),
	side(side),
	hand(dimensions, side, robotState)
{}

void ForeArm::Initialise()
{
    dimensions.forearmWidth = 50.0f;
    dimensions.forearmHeight = 120.0f;

    Shape::drawGeometry.width = dimensions.forearmWidth;
    Shape::drawGeometry.height = dimensions.forearmHeight;

    hand.Initialise();

    positionOffset = 
    {
        0,
        0
    };

    Shape::drawGeometry.origin = {
        Shape::drawGeometry.width / 2.0f,
        0
    };
}


void ForeArm::Update(float dt)
{
    if(waveState != WaveState::None)
    {
        AdvanceWave(dt);
    }

    if(shrugState != ShrugState::None)
    {
        AdvanceShrug(dt);
    }

    hand.Update(dt);
}

void ForeArm::Draw() const 
{
    Shape::Draw();
    hand.Draw();
}

void ForeArm::SetTransform(MyTransform parentTransform)
{
    tempParentTransform = parentTransform;

    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::transform.rotation += localRotation;
    Shape::SetScreenCoords();

    hand.SetTransform(Shape::transform);
}

void ForeArm::Wave()
{
    if(waveState == WaveState::None)
    {
        waveState = WaveState::Raising;
    }
}

void ForeArm::AdvanceWave(float dt)
{
    if(side == "left")
    {
        const float speed = 400.0f;
        const float minRotation = 0.0f;
        const float maxRotation = 90.0f;
        
        if(waveState == WaveState::Raising)
        {
            localRotation += speed * dt;
            
            if(localRotation >= maxRotation)
            {
                localRotation = maxRotation;
                waveState = WaveState::Lowering;
            }
        }
        else if(waveState == WaveState::Lowering)
        {
            localRotation -= speed * dt;

            if(localRotation <= minRotation)
            {
                localRotation = minRotation;
                
                if(robotState.gestures.waveLeft)
                {
                    waveState = WaveState::Raising;
                }
                else {
                    waveState = WaveState::None;
                }
            }
        }
    }

    if(side == "right")
    {
        const float speed = 400.0f;
        const float minRotation = 0.0f;
        const float maxRotation = -90.0f;

        if(waveState == WaveState::Raising)
        {
            localRotation -= speed * dt;
            
            if(localRotation <= maxRotation)
            {
                localRotation = maxRotation;
                waveState = WaveState::Lowering;
            }
        }
        else if(waveState == WaveState::Lowering)
        {
            localRotation += speed * dt;

            if(localRotation >= minRotation)
            {
                localRotation = minRotation;
                
                if(robotState.gestures.waveRight)
                {
                    waveState = WaveState::Raising;
                }
                else {
                    waveState = WaveState::None;
                }
            }
        }
    }

    SetTransform(tempParentTransform);
}

void ForeArm::Shrug()
{
    if(shrugState == ShrugState::None)
    {
        shrugState = ShrugState::Raising;
    }
}

void ForeArm::AdvanceShrug(float dt)
{
    float shrugMax = 60.0f;

    if(side == "left")
    {
        const float speed = 250.0f;
        const float minRotation = 0.0f;
        const float maxRotation = shrugMax;

        if(shrugState == ShrugState::Raising)
        {
            localRotation += speed * dt;
            
            if(localRotation >= maxRotation)
            {
                localRotation = maxRotation;
                shrugState = ShrugState::Shrugging;
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
            localRotation -= speed * dt;

            if(localRotation <= minRotation)
            {
                localRotation = minRotation;
                shrugState = ShrugState::None;
            }
        }
    }

    if(side == "right")
    {
        const float speed = 250.0f;
        const float minRotation = 0.0f;
        const float maxRotation = -shrugMax;

        if(shrugState == ShrugState::Raising)
        {
            localRotation -= speed * dt;
            
            if(localRotation <= maxRotation)
            {
                localRotation = maxRotation;
                shrugState = ShrugState::Shrugging;
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
            localRotation += speed * dt;

            if(localRotation >= minRotation)
            {
                localRotation = minRotation;
                shrugState = ShrugState::None;
            }
        }
    }

    SetTransform(tempParentTransform);    
}