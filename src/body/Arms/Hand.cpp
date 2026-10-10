#include "Body/Arms/Hand.h"

Hand::Hand
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& robotState
) :
	Shape(CARDBOARD_DARK),
    dimensions(dimensions),
    robotState(robotState),
	side(side),
    clamp(dimensions, robotState)
{}

void Hand::Initialise()
{
    dimensions.handWidth = 55.0f;
    dimensions.handHeight = 50.0f;

    drawGeometry.width = dimensions.handWidth;
    drawGeometry.height = dimensions.handHeight;

    positionOffset = {
        0,
        -dimensions.forearmHeight
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    clamp.Initialise();
}

void Hand::Update(float dt)
{
    clamp.Update(dt);
}

void Hand::Draw() const 
{
    Shape::Draw();
    clamp.Draw();
}

void Hand::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
    clamp.SetTransform(transform);
}

void Hand::CloseClamp()
{
    clamp.CloseClamp();
}

void Hand::OpenClamp()
{
    clamp.OpenClamp();
}