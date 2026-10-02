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

void ForeArm::SetWaveState(WaveState waveState)
{
    this->waveState = waveState;
}

void ForeArm::WaveArm()
{
    if(waveState == WaveState::None)
    {
        waveState = WaveState::Raising;
    }
}

void ForeArm::AdvanceWave(float dt)
{
    const float speed = 400.0f;
    float minRotation = 0.0f;
    float maxRotation = 0.0f;

    if(side == "right")
    {
        minRotation = 0.0f;
        maxRotation = -90.0f;
    }

    if(side == "left")
    {
        minRotation = 0.0f;
        maxRotation = 90.0f;
    }
        
    if(waveState == WaveState::Raising)
    {
        localRotation -= speed * dt;
        
        if(localRotation <= maxRotation)
        {
            localRotation = maxRotation;
            waveState = WaveState::Lowering;
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
            
            if(robotState.gestures.waveRight)
            {
                waveState = WaveState::Raising;
            }
            else {
                waveState = WaveState::None;
            }
        }
    }

    SetTransform(tempParentTransform);
}