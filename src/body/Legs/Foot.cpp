#include "Body/Legs/Foot.h"

Foot::Foot(BodyDimensions& dimensions, std::string side) :
	Shape(CARDBOARD_DARK),
	dimensions(dimensions),
	side(side)

{}

void Foot::Initialise()
{
	dimensions.footWidth = 100.0f; 
    dimensions.footHeight = 60.0f;

    Shape::drawGeometry.width = dimensions.footWidth;
    Shape::drawGeometry.height = dimensions.footHeight;

    if(side == "left")
    {
        positionOffset = {
            -dimensions.shinWidth / 2.0f,
            -dimensions.shinHeight
        };
		
		Shape::drawGeometry.origin = {
        	0,
        	Shape::drawGeometry.height / 2.0f
    	};
    }

    if(side == "right")
    {
        positionOffset = {
			dimensions.shinWidth / 2.0f,
            -dimensions.shinHeight
        };

		Shape::drawGeometry.origin = {
        	Shape::drawGeometry.width,
        	Shape::drawGeometry.height / 2.0f
    	};
    }
}

float kjhr = 0;
void Foot::Update(float dt)
{
	kjhr *= dt;
}

void Foot::Draw() const{
	Shape::Draw();
}

void Foot::SetTransform(MyTransform parentTransform)
{
	Shape::transform = MakeChildTransform(parentTransform, positionOffset);
	Shape::SetScreenCoords();
}
