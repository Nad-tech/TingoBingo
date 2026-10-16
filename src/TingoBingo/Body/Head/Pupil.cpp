#include "TingoBingo/Body/Head/Pupil.h"
#include "raymath.h"

Pupil::Pupil(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Pupil::Initialise()
{
    positionOffset = {
        0.0f, 
        0.0f, 
        dimensions.eye.length / 2.0f + dimensions.pupil.length / 2.0f
    };
}

void Pupil::Update(float dt)
{
    (void)dt;
}

void Pupil::Draw()
{
    DrawModelEx(
        assets.pupil,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Pupil::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}