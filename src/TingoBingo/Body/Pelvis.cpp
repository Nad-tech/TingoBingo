#include "TingoBingo/Body/Pelvis.h"
#include "raymath.h"

Pelvis::Pelvis
(
    TingoAssets& assets, 
    TingoDimensions& dimensions,
    TingoState& state
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    leftThigh(assets, dimensions, "left"),
    rightThigh(assets, dimensions, "right")
{}

void Pelvis::Initialise()
{
    positionOffset = {
        0.0f, 
        -dimensions.bodyShape.height / 2.0f,
        0.0f
    };

    leftThigh.Initialise();
    rightThigh.Initialise();

    localRotation = 0.0f;
}

void Pelvis::Update(float dt)
{
    leftThigh.Update(dt);
    rightThigh.Update(dt);
}

void Pelvis::Draw()
{
    DrawModelEx(
        assets.pelvis,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    leftThigh.Draw();
    rightThigh.Draw();  
}

void Pelvis::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle = localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);

    leftThigh.SetTransform(transform);
    rightThigh.SetTransform(transform);
}

void Pelvis::SetLeftThighLocalRotation(float angle)
{
    leftThigh.SetLocalRotation(angle);
}

void Pelvis::SetRightThighLocalRotation(float angle)
{
    rightThigh.SetLocalRotation(angle);
}

float Pelvis::GetLeftThighLocalRotation()
{
    return leftThigh.GetLocalRotation();
}

float Pelvis::GetRightThighLocalRotation()
{
    return rightThigh.GetLocalRotation();
}