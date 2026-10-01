#include "Body/Legs/Knee.h"
#include "Constants.h"

// Load the head sprite and initialise its animation.
Knee::Knee(BodyDimensions& dimensions, std::string side) :
    Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    side(side),
    shin(dimensions, side)
{}

void Knee::Initialise()
{
    dimensions.kneeWidth = 85.0f; 
    dimensions.kneeHeight = 85.0f;

    Shape::drawGeometry.width = dimensions.kneeWidth;
    Shape::drawGeometry.height = dimensions.kneeHeight;

    if(side == "left")
    {
        positionOffset = {
            0,
            -dimensions.thighHeight
        };
    }

    if(side == "right")
    {
        positionOffset = {
			0,
            -dimensions.thighHeight
        };
    }

    Shape::drawGeometry.origin = {
        Shape::drawGeometry.width / 2.0f,
        Shape::drawGeometry.height / 2.0f
    };

    shin.Initialise();
}

void Knee::Update(float dt, Emotion emotion)
{
    shin.Update(dt, emotion);
}

void Knee::Draw() const
{
    shin.Draw();
    Shape::Draw();
}

void Knee::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    
    Shape::SetScreenCoords();

    shin.SetTransform(Shape::transform);
}