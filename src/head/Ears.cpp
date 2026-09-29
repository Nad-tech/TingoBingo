//====================================================
// Ears.cpp
//
// Handles the robot's ear sprites and animation.
// The ears can play a short wiggle animation when
// triggered.
//====================================================

#include "Body/Head/Ears.h"
#include "Constants.h"

Ears::Ears(BodyDimensions& dimensions) : dimensions(dimensions)
{}

void Ears::Initialise()
{
    dimensions.earsWidth = 100;
    dimensions.earsHeight = 100;

    positionOffset = {0, 0};
}

void Ears::Update(float dt)
{
    idleAnimationTimer += dt;

    if(idleAnimationTimer > nextIdleAnimation)
    { 
        idleAnimationTimer = 0.0f;
        nextIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Ears::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
}
