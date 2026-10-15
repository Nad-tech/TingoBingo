#include "TingoBingo/Body/Leg/Thigh.h"
#include "raymath.h"

Thigh::Thigh(TingoAssets& assets, TingoDimensions& dimensions, std::string side) :
    assets(assets),
    dimensions(dimensions),
    side(side),
    knee(assets, dimensions)
{}

void Thigh::Initialise()
{
    if(side == "left")
    {
        positionOffset = {
        dimensions.pelvis.width / 2.0f - dimensions.thigh.width / 2.0f, 
        -dimensions.pelvis.height / 2.0f -
        dimensions.thigh.height / 2.0f,
        0.0f
        };
    }
    else if (side == "right")
    {
        positionOffset = {
        -dimensions.pelvis.width / 2.0f + dimensions.thigh.width / 2.0f, 
        -dimensions.pelvis.height / 2.0f -
        dimensions.thigh.height / 2.0f,
        0.0f
        };
    }

    knee.Initialise();
}

void Thigh::ShutDown()
{
    
}

void Thigh::Update(float dt)
{
    (void)dt;
}

void Thigh::Draw()
{
    DrawModelEx(
        assets.thigh,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.thigh,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    knee.Draw();
}

void Thigh::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    knee.SetTransform(transform);
}