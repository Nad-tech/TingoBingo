#include "Body/Neck.h"
#include "raylib.h"

Neck::Neck(BodyDimensions& dimensions) :
    Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    positionOffset(),
    head(dimensions)
{
}

void Neck::Initialise() 
{
    dimensions.neckWidth = 50.0f;
    dimensions.neckHeight = 30.0f;

    drawGeometry.width = dimensions.neckWidth;
    drawGeometry.height = dimensions.neckHeight;

    head.Initialise();

    positionOffset = {
        0, 
        dimensions.bodyHeight / 2.0f + dimensions.neckHeight / 2.0f
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    Shape::SetShapeName("neck");
}

void Neck::Update(float dt, bool speaking, Emotion emotion) {
    head.Update(dt, speaking, emotion);
}

void Neck::Draw() const
{
    Shape::Draw();
    head.Draw();
}

void Neck::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::SetScreenCoords();

    head.SetTransform(transform);
}

Head& Neck::GetHead()
{
    return head;
}

void Neck::Shutdown()
{
    head.Shutdown();
}