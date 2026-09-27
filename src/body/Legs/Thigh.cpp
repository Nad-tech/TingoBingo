#include "body/Legs/Thigh.h"
#include "Constants.h"
#include <string>

// Load the head sprite and initialise its animation.
Thigh::Thigh(BodyDimensions& dimensions, std::string side) :
    Shape(CARDBOARD),
    dimensions(dimensions),
    side(side)
{}

void Thigh::Initialise()
{
    // Calculate the size of a single animation frame.
    dimensions.thighWidth = 80.0f; 
    dimensions.thighHeight = 250.0f;

    Shape::SetDimensions(
        dimensions.thighWidth, 
        dimensions.thighHeight
    );

    if(side == "left")
    {
        positionOffset = {
            dimensions.pelvisWidth / 2.0f - 
            dimensions.thighWidth / 2.0f,
            -dimensions.thighHeight / 2.0f
        };
    }

    if(side == "right")
    {
        positionOffset = {
            -dimensions.pelvisWidth / 2.0f + 
            dimensions.thighWidth / 2.0f,
            -dimensions.thighHeight / 2.0f
        };
    }
    

}

void Thigh::Update(float dt)
{
    knee.Update(dt);
}

void Thigh::Draw() const
{
    Shape::Draw();
}

void Thigh::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    knee.SetAnchorPoint({0,0});
}