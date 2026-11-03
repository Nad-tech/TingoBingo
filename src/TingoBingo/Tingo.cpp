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
    vision.Initialise();
}

void Tingo::ShutDown()
{
    assets.ShutDown();
}

void Tingo::Update(float dt, const std::vector<GameObject*>& gameObjects)
{
    tingoBrain.Update(dt);
    body.Update(dt);

    vision.Update(
        GetVisionPosition(),
        GetHeadForwardDirection(),
        gameObjects
    );
}

void Tingo::Draw()
{
    body.Draw();
    vision.Draw();
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

void Tingo::UpdateVision(const std::vector<GameObject*>& objects)
{
    vision.Update(
        GetVisionPosition(),
        GetHeadForwardDirection(),
        objects
    );
}

const std::vector<GameObject*>& Tingo::GetVisibleObjects() const
{
    return vision.GetVisibleObjects();
}

Vector3 Tingo::GetVisionPosition() const
{
    return body.GetVisionPosition();
}

Vector3 Tingo::GetHeadForwardDirection() const
{
    return body.GetHeadForwardDirection();
}

Body& Tingo::GetBody()
{
    return body;
}