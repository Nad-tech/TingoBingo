#include "TingoBingo/Body/Neck.h"
#include "TingoBingo/TingoColours.h"
#include "raymath.h"

Neck::Neck(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Neck::Initialise()
{
    positionOffset = {
        0.0f,
        dimensions.bodyShape.height / 2.0f +
        dimensions.neck.height / 2.0f,
        0.0f
    };
}

void Neck::ShutDown()
{
    
}

void Neck::Update(float dt)
{
    (void)dt;
}

void Neck::Draw()
{
    DrawModelEx(
        assets.neck,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.neck,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );
}

void Neck::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
}