#include "TingoBingo/Body/Leg/Shin.h"
#include "raymath.h"

Shin::Shin(TingoAssets& assets,TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    foot(assets, dimensions)
{}

void Shin::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.knee.height / 2.0f
        -dimensions.shin.height / 2.0f,
        0.0f
    };

    foot.Initialise();
}

void Shin::Update(float dt)
{
    (void)dt;
}

void Shin::Draw()
{
    DrawModelEx(
        assets.shin,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    foot.Draw();
}

void Shin::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    foot.SetTransform(transform);
}

