#include "TingoBingo/Body/Head/EyeBrow.h"
#include "raymath.h"

EyeBrow::EyeBrow
(
    TingoAssets& assets, 
    TingoDimensions& dimensions, 
    std::string side
) :
    assets(assets),
    dimensions(dimensions),
    side(side)
{}

void EyeBrow::Initialise()
{
    float Xoffset = 0.5f;
    float Yoffset = 0.7f;

    if(side == "left")
    {
        positionOffset = {
            Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f + 
            dimensions.eyeBrow.length / 2.0f        
        };
    }
    else if(side == "right")
    {
        positionOffset = {
            -Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f +
            dimensions.eyeBrow.length / 2.0f       
        };
    }
}

void EyeBrow::Update(float dt)
{
    (void)dt;
}

void EyeBrow::Draw()
{
    DrawModelEx(
        assets.eyeBrow,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void EyeBrow::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}