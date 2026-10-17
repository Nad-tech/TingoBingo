#include "TingoBingo/Body/Arm/UpperArm.h"
#include "raymath.h"

UpperArm::UpperArm(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    elbow(assets, dimensions)
{}


void UpperArm::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.shoulder.height / 2.0f,
        0.0f
    };
    
    elbow.Initialise();
}

void UpperArm::Update(float dt)
{
    (void)dt;

    //dirFlag ? localRotation += dt * 80 : localRotation -= dt * 80;
    
    if(localRotation <= -45) dirFlag = true;
    if(localRotation >= 45) dirFlag = false;

    SetTransform(tempParentTransform);

    elbow.Update(dt);
}

void UpperArm::Draw()
{
    DrawModelEx(
        assets.upperArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    elbow.Draw();
}

void UpperArm::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    elbow.SetTransform(transform);
}