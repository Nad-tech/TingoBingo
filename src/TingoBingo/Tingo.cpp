#include "TingoBingo/Tingo.h"
#include "raymath.h"

#include <iostream>

Tingo::Tingo(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    body(assets, dimensions)
{}

void Tingo::Initialise()
{
    body.Initialise();
}

void Tingo::ShutDown()
{
    assets.ShutDown();
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