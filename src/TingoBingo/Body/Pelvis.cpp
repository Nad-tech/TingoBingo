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
        -dimensions.bodyShape.height / 2.0f,
        0.0f
    };

    leftThigh.Initialise();
    rightThigh.Initialise();
}

void Pelvis::Update(float dt)
{
    //dirFlag ? localRotation += dt * 80 : localRotation -= dt * 80;

    if(localRotation <= -45) dirFlag = true;
    if(localRotation >= 45) dirFlag = false;

    SetTransform(tempParentTransform);

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
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);

    leftThigh.SetTransform(transform);
    rightThigh.SetTransform(transform);
}