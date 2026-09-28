#include "Body/Neck.h"
#include "raylib.h"

Neck::Neck(BodyDimensions& dimensions) :
    dimensions(dimensions),
    positionOffset(),
    head(dimensions)
{
}

void Neck::Initialise() 
{
    dimensions.neckWidth = 50.0f;
    dimensions.neckHeight = 30.0f;
    SetDimensions(dimensions.neckWidth, dimensions.neckHeight);

    head.Initialise();

    positionOffset = {
        0, 
        dimensions.bodyHeight / 2.0f + dimensions.neckHeight / 2.0f
    };
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