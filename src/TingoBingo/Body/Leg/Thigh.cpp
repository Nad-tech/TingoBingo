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

void Thigh::Update(float dt)
{
    (void)dt;

    //dirFlag ? localRotation += dt * 80 : localRotation -= dt * 80;

    if(localRotation <= -45) dirFlag = true;
    if(localRotation >= 45) dirFlag = false;

    SetTransform(tempParentTransform);

    knee.Update(dt);
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

    knee.Draw();
}

void Thigh::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    knee.SetTransform(transform);
}