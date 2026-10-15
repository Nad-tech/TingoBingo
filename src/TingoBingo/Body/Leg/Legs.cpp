#include "TingoBingo/Body/Leg/Legs.h"

Legs::Legs(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    leftThigh(assets, dimensions, "left"),
    rightThigh(assets, dimensions, "right")
{}

void Legs::Initialise()
{
   leftThigh.Initialise();
   rightThigh.Initialise();
}

void Legs::ShutDown()
{
    leftThigh.ShutDown();
    rightThigh.ShutDown();
}

void Legs::Update(float dt)
{
    leftThigh.Update(dt);
    rightThigh.Update(dt);
}

void Legs::Draw()
{
    leftThigh.Draw();
    rightThigh.Draw();
}

void Legs::SetTransform(MyTransform3D parentTransform)
{
    leftThigh.SetTransform(parentTransform);
    rightThigh.SetTransform(parentTransform);
}