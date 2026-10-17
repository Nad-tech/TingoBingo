#include "TingoBingo/Body/Arm/Finger.h"
#include "raymath.h"

Finger::Finger(TingoAssets& assets, TingoDimensions& dimensions, std::string side) :
    assets(assets),
    dimensions(dimensions),
    side(side)
{}


void Finger::Initialise()
{
    if(side == "left")
    {
        positionOffset = {
            dimensions.hand.width / 2.0f - dimensions.finger.width / 2.0f,
            -dimensions.hand.height / 2.0f,
            0.0f
        };
    }
    else if (side == "right")
    {
        positionOffset = {
            -dimensions.hand.width / 2.0f + dimensions.finger.width / 2.0f,
            -dimensions.hand.height / 2.0f,
            0.0f
        };
    }
}

void Finger::Update(float dt)
{
    (void)dt;
}

void Finger::Draw()
{
    DrawModelEx(
        assets.finger,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Finger::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    
    if(side == "left")
    {
        localTransform.rotationAxis = {0.0f, 0.0f, 1.0f};
        localTransform.rotationAngle = -15.0f;
    }
    else if(side == "right")
    {
        localTransform.rotationAxis = {0.0f, 0.0f, 1.0f};
        localTransform.rotationAngle = 15.0f;
    }

    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}