#include "body/Arms/Clamp.h"

Clamp::Clamp(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    leftFinger(dimensions, "left", robotState),
    rightFinger(dimensions, "right", robotState)
{}

void Clamp::Initialise()
{
    leftFinger.Initialise();
    rightFinger.Initialise();
}

void Clamp::Shutdown()
{};

void Clamp::Update(float dt)
{
    leftFinger.Update(dt);
    rightFinger.Update(dt);
}

void Clamp::Draw() const
{
    leftFinger.Draw();
    rightFinger.Draw();
}
        
void Clamp::SetTransform(MyTransform parentTransform)
{
    leftFinger.SetTransform(parentTransform);
    rightFinger.SetTransform(parentTransform);
}

void Clamp::OpenClamp()
{
    leftFinger.Open();
    rightFinger.Open();
}

void Clamp::CloseClamp()
{
    leftFinger.Close();
    rightFinger.Close();
}