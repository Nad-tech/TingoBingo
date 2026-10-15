#include "TingoBingo/Body/Arm/Elbow.h"
#include "raymath.h"

Elbow::Elbow(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    foreArm(assets, dimensions)
{}


void Elbow::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.upperArm.height / 2.0f - dimensions.elbow.height / 2.0f, 
        0.0f
    };

    foreArm.Initialise();
}

void Elbow::ShutDown()
{
    
}

void Elbow::Update(float dt)
{
    (void)dt;
}

void Elbow::Draw()
{
    DrawModelEx(
        assets.elbow,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.elbow,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    foreArm.Draw();
}

void Elbow::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    foreArm.SetTransform(transform);
}