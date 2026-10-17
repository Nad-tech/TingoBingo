#include "TingoBingo/Body/Arm/ForeArm.h"
#include "raymath.h"

ForeArm::ForeArm(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    hand(assets, dimensions)
{}


void ForeArm::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.elbow.height / 2.0f,
        0.0f
    };

    hand.Initialise();
}

void ForeArm::Update(float dt)
{
    (void)dt;

    //dirFlag ? localRotation += dt * 80 : localRotation -= dt * 80;

    if(localRotation <= -45) dirFlag = true;
    if(localRotation >= 45) dirFlag = false;

    SetTransform(tempParentTransform);

    hand.Update(dt);
}

void ForeArm::Draw()
{
    DrawModelEx(
        assets.foreArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    hand.Draw();
}

void ForeArm::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    hand.SetTransform(transform);
}
