#include "Body/Arms/Hand.h"

Hand::Hand(BodyDimensions& dimensions, std::string side) :
	Shape(CARDBOARD_DARK),
    dimensions(dimensions),
	side(side)
{}

void Hand::Initialise()
{
    dimensions.handWidth = 55.0f;
    dimensions.handHeight = 50.0f;

    positionOffset = {
        0,
        -dimensions.forearmHeight / 2.0f
    };
}

float r = 0.0f;
void Hand::Update(float dt)
{
    r += dt*50.0;
}

void Hand::Draw() const 
{
    Shape::Draw();
}

void Hand::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
}