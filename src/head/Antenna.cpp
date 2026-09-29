//====================================================
// Antenna.cpp
//
// Handles the robot's antenna sprite and animation.
// The antenna can play a short wiggle animation when
// triggered.
//====================================================

#include "Body/Head/Antenna.h"
#include "Constants.h"

Antenna::Antenna(BodyDimensions& dimensions) : dimensions(dimensions)
{}

void Antenna::Initialise()
{
    dimensions.antennaWidth = 100;
    dimensions.antennaHeight = 100;

    positionOffset = {
        0,
        topOfHeadOffset
    };
}

void Antenna::Update(float dt)
{
    //Idle behavior
    //Wiggle the antenna at random intervals
    antennaAnimationTimer += dt;

    if (antennaAnimationTimer > nextAntennaAnimation)
    {
        antennaAnimationTimer = 0.0f;
        nextAntennaAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Antenna::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
}
