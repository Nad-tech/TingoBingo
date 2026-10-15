#include "TingoBingo/Body/Pelvis.h"
#include "raymath.h"

Pelvis::Pelvis(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    leftThigh(assets, dimensions, "left"),
    rightThigh(assets, dimensions, "right")
{}

void Pelvis::Initialise()
{
    positionOffset = {
        0.0f, 
        -dimensions.bodyShape.height / 2.0f - 
        dimensions.pelvis.height / 2.0f,
        0.0f
    };

    leftThigh.Initialise();
    rightThigh.Initialise();
}

void Pelvis::ShutDown()
{
    
}

void Pelvis::Update(float dt)
{
    (void)dt;
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

    leftThigh.Draw();
    rightThigh.Draw();  
}

void Pelvis::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    leftThigh.SetTransform(transform);
    rightThigh.SetTransform(transform);
}