#include "TingoBingo/Body/Head/Nose.h"
#include "raymath.h"

Nose::Nose(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Nose::Initialise()
{
    positionOffset = {
        0.0f, 0.0f, dimensions.head.length / 2.0f + dimensions.nose.length / 2.0f
    };
}

void Nose::Update(float dt)
{
    (void)dt;
}

void Nose::Draw()
{
    DrawModelEx(
        assets.nose,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Nose::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}