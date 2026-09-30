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

    hand.Initialise();

    positionOffset = 
    {
        0,
        -dimensions.forearmHeight / 2.0f
    };

    
}

//float rt = 0.0f;
void ForeArm::Update(float dt)
{
    hand.Update(dt);
    //rt += dt*50.0f;
}

void ForeArm::Draw() const 
{
    Shape::Draw();
    hand.Draw();
}

void ForeArm::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    //transform.rotation += rt;
    hand.SetTransform(Shape::transform);
}
