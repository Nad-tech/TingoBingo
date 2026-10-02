#include "Body/Legs/Shin.h"

Shin::Shin(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
	Shape(CARDBOARD),
	dimensions(dimensions),
    robotState(robotState),
	side(side),
    foot(dimensions, side, robotState)
{}

void Shin::Initialise()
{
    dimensions.shinWidth = 70.0f; 
    dimensions.shinHeight = 150.0f;

    Shape::drawGeometry.width = dimensions.shinWidth;
    Shape::drawGeometry.height = dimensions.shinHeight;

    if(side == "left")
    {
        positionOffset = {
            0,
            0
        };
    }

    if(side == "right")
    {
        positionOffset = {
			0,
            0
        };
    }

    Shape::drawGeometry.origin = {
        Shape::drawGeometry.width / 2.0f,
        0
    };

	foot.Initialise();
}

void Shin::Update(float dt)
{
    foot.Update(dt);
}

void Shin::Draw() const
{
    Shape::Draw();
	foot.Draw();
}

void Shin::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::SetScreenCoords();

	foot.SetTransform(Shape::transform);
}