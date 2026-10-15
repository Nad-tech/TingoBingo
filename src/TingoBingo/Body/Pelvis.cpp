#include "TingoBingo/Body/Pelvis.h"
#include "TingoBingo/TingoColours.h"
#include "raymath.h"

Pelvis::Pelvis(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    legs(assets, dimensions)
{}

void Pelvis::Initialise()
{
    positionOffset = {
        0.0f, 
        -dimensions.bodyShape.height / 2.0f - 
        dimensions.pelvis.height / 2.0f,
        0.0f
    };

    legs.Initialise();
}

void Pelvis::ShutDown()
{
    legs.ShutDown();
}

void Pelvis::Update(float dt)
{
    legs.Update(dt);
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

    DrawModelWiresEx(
        assets.pelvis,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    legs.Draw();
}

void Pelvis::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    legs.SetTransform(transform);
}