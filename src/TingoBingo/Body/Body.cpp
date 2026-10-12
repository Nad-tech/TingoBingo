#include "TingoBingo/Body/Body.h"

void Body::Initialise()
{
    bodyShape.Initialise();
}

void Body::ShutDown()
{
    bodyShape.ShutDown();
}

void Body::Update(float dt)
{
    bodyShape.Update(dt);
}

void Body::Draw()
{
    bodyShape.Draw();
}

void Body::SetTransform(MyTransform3D initialTransform)
{
    transform = initialTransform;
    bodyShape.SetTransform(transform);
}