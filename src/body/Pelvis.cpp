#include "Body/Pelvis.h"
#include "raymath.h"

Pelvis::Pelvis(BodyDimensions& dimensions) :
    dimensions(dimensions),
    legs(dimensions)
{}
void Pelvis::Initialise()
{
    dimensions.pelvisWidth = 240.0f;
    dimensions.pelvisHeight = 70.0f;
    SetDimensions(dimensions.pelvisWidth, dimensions.pelvisHeight);

    legs.Initialise();

    positionOffset = {
        0,
        -dimensions.bodyHeight / 2.0f - dimensions.pelvisHeight / 2.0f
    };
}

void Pelvis::Update(float dt)
{
    legs.Update(dt);
}

void Pelvis::Draw() const 
{
    legs.Draw();
    Shape::Draw();
}

void Pelvis::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);

    Shape::SetTransform(transform);
    legs.SetTransform(transform);
}

void Pelvis::Shutdown()
{
    legs.Shutdown();
}