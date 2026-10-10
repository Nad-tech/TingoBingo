#include "Body/Arms/Arms.h"

Arms::Arms(BodyDimensions& dimensions, RobotState& robotState) : 
    dimensions(dimensions),
    robotState(robotState),
    leftShoulder(dimensions, "left", robotState),
    rightShoulder(dimensions, "right", robotState)
{
}

void Arms::Initialise()
{
    leftShoulder.Initialise();
    rightShoulder.Initialise();
}

void Arms::Shutdown()
{
}

void Arms::Update(float dt)
{
    Wave();
    Shrug();
    OpenOrCloseClamp();

    leftShoulder.Update(dt);
    rightShoulder.Update(dt);
}

void Arms::Draw() const 
{
    leftShoulder.Draw();
    rightShoulder.Draw();
}

void Arms::SetTransform(MyTransform parentTransform)
{
    leftShoulder.SetTransform(parentTransform);
    rightShoulder.SetTransform(parentTransform);
}

void Arms::Wave()
{
    if(robotState.gestures.waveRight) {
        rightShoulder.Wave();
    }

    if(robotState.gestures.waveLeft)
    {
        leftShoulder.Wave();
    }
}

void Arms::Shrug()
{
    if(robotState.gestures.shrug)
    {
        leftShoulder.Shrug();
        rightShoulder.Shrug();
    }
}

void Arms::OpenOrCloseClamp()
{
    if(robotState.gestures.closeLeftClamp)
    {
        leftShoulder.CloseClamp();
    }
    else
    {
        leftShoulder.OpenClamp();
    }


    if(robotState.gestures.closeRightClamp)
    {
        rightShoulder.CloseClamp();
    }
    else
    {
        rightShoulder.OpenClamp();
    }
}