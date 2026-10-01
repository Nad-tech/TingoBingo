#include "Body/Arms/ForeArm.h"

ForeArm::ForeArm(BodyDimensions& dimensions, std::string side) :
	Shape(CARDBOARD_LIGHT),
    dimensions(dimensions),
	side(side),
	hand(dimensions, side)
{}

void ForeArm::Initialise()
{
    dimensions.forearmWidth = 50.0f;
    dimensions.forearmHeight = 120.0f;

    Shape::drawGeometry.width = dimensions.forearmWidth;
    Shape::drawGeometry.height = dimensions.forearmHeight;

    hand.Initialise();

    positionOffset = 
    {
        0,
        0
    };

    Shape::drawGeometry.origin = {
        Shape::drawGeometry.width / 2.0f,
        0
    };
}


void ForeArm::Update(float dt, Emotion emotion)
{
    hand.Update(dt, emotion);
}

void ForeArm::Draw() const 
{
    Shape::Draw();
    hand.Draw();
}

void ForeArm::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);

    float angle = -20.0f;
    if(side == "left") angle = 20.0f; 
    Shape::transform.rotation += angle;

    Shape::SetScreenCoords();

    hand.SetTransform(Shape::transform);
}
