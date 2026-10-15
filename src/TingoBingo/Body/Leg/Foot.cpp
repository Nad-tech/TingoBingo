#include "TingoBingo/Body/Leg/Foot.h"
#include "TingoBingo/TingoColours.h"
#include "raymath.h"

Foot::Foot(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Foot::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.shin.height / 2.0f
        -dimensions.foot.height / 2.0f,
        dimensions.foot.length / 2.0f
        -dimensions.shin.length / 2.0f
    };
}

void Foot::ShutDown()
{
    
}

void Foot::Update(float dt)
{
    (void)dt;
}

void Foot::Draw()
{
    DrawModelEx(
        assets.foot,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.foot,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );
}

void Foot::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
}