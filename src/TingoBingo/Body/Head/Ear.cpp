#include "TingoBingo/Body/Head/Ear.h"
#include "raymath.h"

Ear::Ear
(
    TingoAssets& assets, 
    TingoDimensions& dimensions, 
    std::string side
) :
    assets(assets),
    dimensions(dimensions),
    side(side)
{}

void Ear::Initialise()
{
    float Xoffset = dimensions.head.width /2.0f +
                    dimensions.ear.width / 2.0f;

    float Yoffset = dimensions.head.height / 2.0f;

    if(side == "left")
    {
        positionOffset = {
            Xoffset,
            Yoffset,
            0.0f        
        };
    }
    else if(side == "right")
    {
        positionOffset = {
            -Xoffset,
            Yoffset,
            0.0f
        };
    }
}

void Ear::Update(float dt)
{
    (void)dt;
}

void Ear::Draw()
{
    DrawModelEx(
        assets.ear,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Ear::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}