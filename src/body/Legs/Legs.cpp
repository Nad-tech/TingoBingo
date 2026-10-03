#include "Body/Legs/Legs.h"

Legs::Legs(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    rightThigh(dimensions, "right", robotState),
    leftThigh(dimensions, "left", robotState)
{}

void Legs::Initialise()
{
    leftThigh.Initialise();
    rightThigh.Initialise();
}

void Legs::Shutdown()
{
   
}

void Legs::Update(float dt)
{
    leftThigh.Update(dt);
    rightThigh.Update(dt);
}

void Legs::Draw() const
{
    leftThigh.Draw();
    rightThigh.Draw();
}

void Legs::SetTransform(MyTransform parentTransform)
{
    leftThigh.SetTransform(parentTransform);
    rightThigh.SetTransform(parentTransform);
}

void Legs::Crouch()
{
    leftThigh.Crouch();
    rightThigh.Crouch();
}

