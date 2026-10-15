#include "TingoBingo/Body/Leg/Knee.h"
#include "TingoBingo/TingoColours.h"
#include "raymath.h"

Knee::Knee(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    shin(assets, dimensions)
{}

void Knee::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.knee.height / 2.0f
        -dimensions.shin.height / 2.0f,
        0.0f
    };

    shin.Initialise();
}

void Knee::ShutDown()
{
    
}

void Knee::Update(float dt)
{
    (void)dt;
}

void Knee::Draw()
{
    DrawModelEx(
        assets.knee,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.knee,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    shin.Draw();
}

void Knee::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    shin.SetTransform(transform);
}