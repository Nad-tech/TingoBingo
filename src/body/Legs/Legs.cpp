#include "body/Legs/Legs.h"

Legs::Legs(BodyDimensions& dimensions) :
    dimensions(dimensions),
    leftThigh(dimensions, "left"),
    rightThigh(dimensions, "right")
{}

void Legs::Initialise()
{
    leftThigh.Initialise();
    rightThigh.Initialise();
}

void Legs::Shutdown()
{
    leftThigh.Shutdown();
    rightThigh.Shutdown();
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

