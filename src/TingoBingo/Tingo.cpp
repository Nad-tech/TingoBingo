#include "TingoBingo/Tingo.h"

void Tingo::Initialise()
{
    body.Initialise();
}

void Tingo::ShutDown()
{
    body.ShutDown();
}

void Tingo::Update(float dt)
{
    body.Update(dt);
}

void Tingo::Draw()
{
    body.Draw();
}

void Tingo::SetTransform(MyTransform3D initialTransform)
{
    transform = initialTransform;
    body.SetTransform(transform);
}