//====================================================
// HeadBase.cpp
//
// Handles the robot's main head sprite.
//
// The HeadBase is responsible for displaying the
// current head orientation and managing rotation
// between head frames.
//====================================================

#include "Body/Head/Headbase.h"
#include "Constants.h"
#include "raylib.h"

Headbase::Headbase(BodyDimensions& dimensions) : 
    dimensions(dimensions)
{}

// Load the head sprite and initialise its animation.
void Headbase::Initialise()
{
    dimensions.headWidth = 100;
    dimensions.headHeight = 100;


    positionOffset = {0.0f, 0.0f};
}

void Headbase::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
}
