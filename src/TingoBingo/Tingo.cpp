#include "TingoBingo/Tingo.h"
#include "raymath.h"

#include <iostream>

Tingo::Tingo(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    body(assets, dimensions, state),
    tingoBrain(*this, state)
{}

void Tingo::Initialise()
{
    body.Initialise();
    tingoBrain.Initialise();
}

void Tingo::ShutDown()
{
    assets.ShutDown();
}

void Tingo::Update(float dt)
{
    tingoBrain.Update(dt);
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

TingoState& Tingo::GetState()
{
    return state;
}

ArmWaveState Tingo::GetLeftArmWaveState() const
{
    return body.GetLeftArmWaveState();
}

ArmWaveState Tingo::GetRightArmWaveState() const
{
    return body.GetRightArmWaveState();
}

EyeState Tingo::GetLeftEyeState() const
{
    return body.GetLeftEyeState();
}

EyeState Tingo::GetRightEyeState() const
{
    return body.GetRightEyeState();
}

MyTransform3D& Tingo::GetTransform()
{
    return transform;
}

void Tingo::SetGazeTarget(Vector2 target)
{
    body.SetGazeTarget(target);
}