#include "Body\Head\EyeBrows.h"

EyeBrows::EyeBrows(BodyDimensions& dimensions, RobotState& robotState) :
        dimensions(dimensions),
        robotState(robotState),
        leftEyeBrow(dimensions, "left", robotState),
        rightEyeBrow(dimensions, "right", robotState)
{}
        
void EyeBrows::Initialise()
{
    leftEyeBrow.Initialise();
    rightEyeBrow.Initialise();
}

void EyeBrows::ShutDown()
{
    leftEyeBrow.ShutDown();
    rightEyeBrow.ShutDown();
}

void EyeBrows::Update(float dt)
{
    leftEyeBrow.Update(dt);
    rightEyeBrow.Update(dt);
}

void EyeBrows::Draw() const
{
    leftEyeBrow.Draw();
    rightEyeBrow.Draw();
}

void EyeBrows::SetTransform(MyTransform parentTransform)
{
    leftEyeBrow.SetTransform(parentTransform);
    rightEyeBrow.SetTransform(parentTransform);
}