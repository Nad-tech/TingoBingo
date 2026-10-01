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

    Shape::drawGeometry.width = dimensions.pelvisWidth;
    Shape::drawGeometry.height = dimensions.pelvisHeight;

    legs.Initialise();

    positionOffset = {
        0,
        -dimensions.bodyHeight / 2.0f - dimensions.pelvisHeight / 2.0f
    };

    Shape::drawGeometry.origin = {
        Shape::drawGeometry.width / 2.0f,
        Shape::drawGeometry.height / 2.0f
    };
}

void Pelvis::Update(float dt, Emotion emotion)
{
    legs.Update(dt, emotion);
}

void Pelvis::Draw() const 
{
    legs.Draw();
    Shape::Draw();
}

void Pelvis::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::SetScreenCoords();

    legs.SetTransform(transform);
}

void Pelvis::Shutdown()
{
    legs.Shutdown();
}