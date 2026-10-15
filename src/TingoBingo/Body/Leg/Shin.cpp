#include "TingoBingo/Body/Leg/Shin.h"
#include "raymath.h"

Shin::Shin(TingoAssets& assets,TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    foot(assets, dimensions)
{}

void Shin::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.knee.height / 2.0f
        -dimensions.shin.height / 2.0f,
        0.0f
    };

    foot.Initialise();
}

void Shin::ShutDown()
{
    
}

void Shin::Update(float dt)
{
    (void)dt;
}

void Shin::Draw()
{
    DrawModelEx(
        assets.shin,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.shin,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    foot.Draw();
}

void Shin::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    foot.SetTransform(transform);
}

