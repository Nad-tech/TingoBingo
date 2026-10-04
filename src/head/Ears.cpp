#include "Body\Head\Ears.h"

Ears::Ears(BodyDimensions& dimensions, RobotState& robotState) :
        dimensions(dimensions),
        robotState(robotState),
        leftEar(dimensions, "left", robotState),
        rightEar(dimensions, "right", robotState)
{}
        
void Ears::Initialise()
{
    leftEar.Initialise();
    rightEar.Initialise();
}

void Ears::ShutDown()
{
    leftEar.ShutDown();
    rightEar.ShutDown();
}

void Ears::Update(float dt)
{
    leftEar.Update(dt);
    rightEar.Update(dt);
}

void Ears::Draw() const
{
    leftEar.Draw();
    rightEar.Draw();
}

void Ears::SetTransform(MyTransform parentTransform)
{
    leftEar.SetTransform(parentTransform);
    rightEar.SetTransform(parentTransform);
}