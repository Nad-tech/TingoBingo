#include "TingoBingo/Body/Head/Eye.h"
#include "raymath.h"

Eye::Eye(TingoAssets& assets, TingoDimensions& dimensions, std::string side) :
    assets(assets),
    dimensions(dimensions),
    side(side)
{}

void Eye::Initialise()
{
    float Xoffset = 0.5f;
    float Yoffset = 0.3f;

    if(side == "left")
    {
        positionOffset = {
            Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f        
        };
    }
    else if(side == "right")
    {
        positionOffset = {
            -Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f        
        };
    }
}

void Eye::Update(float dt)
{
    (void)dt;
}

void Eye::Draw()
{
    DrawModelEx(
        assets.eye,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Eye::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}