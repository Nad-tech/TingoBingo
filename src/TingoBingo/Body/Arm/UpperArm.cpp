#include "TingoBingo/Body/Arm/UpperArm.h"
#include "raymath.h"

UpperArm::UpperArm(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    elbow(assets, dimensions)
{}


void UpperArm::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.upperArm.height / 2.0f - dimensions.shoulder.height / 2.0f,
        0.0f
    };
    
    elbow.Initialise();
}

void UpperArm::ShutDown()
{
    
}

void UpperArm::Update(float dt)
{
    (void)dt;
}

void UpperArm::Draw()
{
    DrawModelEx(
        assets.upperArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.upperArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    elbow.Draw();
}

void UpperArm::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    elbow.SetTransform(transform);
}