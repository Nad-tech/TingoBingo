#include "TingoBingo/Body/Arm/Hand.h"
#include "raymath.h"

Hand::Hand(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    leftFinger(assets, dimensions, "left"),
    rightFinger(assets, dimensions, "right")
{}


void Hand::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.foreArm.height,
        0.0f
    };

    leftFinger.Initialise();
    rightFinger.Initialise();
}

void Hand::Update(float dt)
{
    (void)dt;

    //dirFlag ? localRotation += dt * 80 : localRotation -= dt * 80;
    
    if(localRotation <= -45) dirFlag = true;
    if(localRotation >= 45) dirFlag = false;

    SetTransform(tempParentTransform);
}

void Hand::Draw()
{
    DrawModelEx(
        assets.hand,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    leftFinger.Draw();
    rightFinger.Draw();
}

void Hand::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    leftFinger.SetTransform(transform);
    rightFinger.SetTransform(transform);
}