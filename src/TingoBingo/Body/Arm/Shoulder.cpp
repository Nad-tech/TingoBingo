#include "TingoBingo/Body/Arm/Shoulder.h"
#include "raymath.h"

Shoulder::Shoulder(TingoAssets& assets, TingoDimensions& dimensions, std::string side) :
    assets(assets),
    dimensions(dimensions),
    side(side),
    upperArm(assets, dimensions)
{}


void Shoulder::Initialise()
{
    if(side == "left")
    {
        positionOffset = {
            dimensions.bodyShape.width / 2.0f + dimensions.shoulder.width / 2.0f,
            dimensions.bodyShape.height / 2.0f - dimensions.shoulder.height / 2.0f,
            0.0f
        };
    }
    else if (side == "right")
    {
        positionOffset = {
            -dimensions.bodyShape.width / 2.0f - dimensions.shoulder.width / 2.0f,
            dimensions.bodyShape.height / 2.0f - dimensions.shoulder.height / 2.0f,
            0.0f
        };
    }

    upperArm.Initialise();
}

void Shoulder::Update(float dt)
{
    (void)dt;
    // localRotation += dt * 80;
}

void Shoulder::Draw()
{
    DrawModelEx(
        assets.shoulder,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
    
    upperArm.Draw();
}

void Shoulder::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    upperArm.SetTransform(transform);
}