#include "Body/Arms/ForeArm.h"

ForeArm::ForeArm
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& RobotState
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
        WaveArm(dt);
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
    Shape::SetScreenCoords();

    hand.SetTransform(Shape::transform);
}

void ForeArm::SetWaveState(WaveState waveState)
{
    this->waveState = waveState;
}

void ForeArm::WaveArm(float dt)
{
    const float speed = 100.0f;
    const float maxRotation = -60.0f;

    if(waveState == WaveState::Raising)
    {
        localRotation -= speed * dt;

        if(localRotation <= maxRotation)
        {
            waveState = WaveState::Lowering;
        }
    }
    else if(waveState == WaveState::Lowering)
    {
        localRotation += speed * dt;

        if(localRotation >= 0.0f)
        {
            localRotation = 0.0f;
        }
    }

    SetTransform(tempParentTransform);
}