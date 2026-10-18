#include "TingoBingo/Body/Leg/Knee.h"
#include "raymath.h"

Knee::Knee(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    shin(assets, dimensions)
{}

void Knee::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.knee.height / 2.0f
        -dimensions.thigh.height,
        0.0f
    };

    shin.Initialise();
}

void Knee::Update(float dt)
{
    shin.Update(dt);
}

void Knee::Draw()
{
    DrawModelEx(
        assets.knee,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    shin.Draw();
}

void Knee::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    shin.SetTransform(transform);
}