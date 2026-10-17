#include "TingoBingo/Body/Head/Antenna.h"
#include "raymath.h"

Antenna::Antenna(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Antenna::Initialise()
{
    float Xoffset = -0.4;
    float Yoffset = dimensions.head.height;
    float Zoffset = -0.4f;

    positionOffset = {
        Xoffset, 
        Yoffset, 
        Zoffset
    };
}

void Antenna::Update(float dt)
{
    (void)dt;
}

void Antenna::Draw()
{
    DrawModelEx(
        assets.antenna,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Antenna::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}