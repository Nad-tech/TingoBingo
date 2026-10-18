#include "TingoBingo/Body/Leg/Foot.h"
#include "raymath.h"

Foot::Foot(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Foot::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.shin.height,
        dimensions.foot.length / 2.0f
        -dimensions.shin.length / 2.0f
    };
}

void Foot::Update(float dt)
{
    (void)dt;
    //dirFlag ? localRotation += dt * 80 : localRotation -= dt * 80;

    if(localRotation <= -45) dirFlag = true;
    if(localRotation >= 45) dirFlag = false;

    SetTransform(tempParentTransform);
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
}

void Foot::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{}; 

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}