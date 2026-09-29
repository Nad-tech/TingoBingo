#include "Body/BodyBase.h"

#include "Constants.h"
#include <iostream>

BodyBase::BodyBase(BodyDimensions& dimensions) :
    Shape(CARDBOARD),
    dimensions(dimensions)
{
}

// Load the body sprite and initialise its animation.
void BodyBase::Initialise()
{
    dimensions.bodyWidth = 240.0f;
    dimensions.bodyHeight = 250.0f;
    Shape::SetDimensions(dimensions.bodyWidth, dimensions.bodyHeight);

    positionOffset = { 0.0f, 0.0f };

    pivot = {0, 0};

    Shape::SetShapeName("bodyBase");
}

void BodyBase::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::transform.pivot = pivot;

    Shape::SetScreenCoords();
}