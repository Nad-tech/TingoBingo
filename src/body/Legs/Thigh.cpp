#include "Body/Legs/Thigh.h"
#include "Constants.h"
#include <string>

// Load the head sprite and initialise its animation.
Thigh::Thigh(BodyDimensions& dimensions, std::string side) :
    Shape(CARDBOARD),
    dimensions(dimensions),
    side(side),
    knee(dimensions, side)
{}

void Thigh::Initialise()
{
    // Calculate the size of a single animation frame.
    dimensions.thighWidth = 80.0f; 
    dimensions.thighHeight = 150.0f;

    Shape::drawGeometry.width = dimensions.thighWidth;
    Shape::drawGeometry.height = dimensions.thighHeight;

    if(side == "left")
    {
        positionOffset = {
            dimensions.pelvisWidth / 2.0f - 
            dimensions.thighWidth / 2.0f,
            0
        };
    }

    if(side == "right")
    {
        positionOffset = {
            -dimensions.pelvisWidth / 2.0f + 
            dimensions.thighWidth / 2.0f,
            0
        };
    }

    Shape::drawGeometry.origin = {
        Shape::drawGeometry.width / 2.0f,
        0
    };

    knee.Initialise();
}

void Thigh::Update(float dt)
{
    knee.Update(dt);
}

void Thigh::Draw() const
{
    Shape::Draw();
    knee.Draw();
}

void Thigh::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    
    float angle = -20.0f;
    if(side == "left") angle = 20.0f; 
    Shape::transform.rotation += angle;

    Shape::SetScreenCoords();

    knee.SetTransform(Shape::transform);
}