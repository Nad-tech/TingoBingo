#include "Body/Legs/Legs.h"

Legs::Legs(BodyDimensions& dimensions) :
    dimensions(dimensions),
    rightThigh(dimensions, "right"),
    leftThigh(dimensions, "left")
{}

void Legs::Initialise()
{
    leftThigh.Initialise();
    rightThigh.Initialise();
}

void Legs::Shutdown()
{
   
}

void Legs::Update(float dt, Emotion emotion)
{
    leftThigh.Update(dt, emotion);
    rightThigh.Update(dt, emotion);
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

