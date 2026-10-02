//====================================================
// Antenna.cpp
//
// Handles the robot's antenna sprite and animation.
// The antenna can play a short wiggle animation when
// triggered.
//====================================================

#include "Body/Head/Antenna.h"
#include "Constants.h"

Antenna::Antenna(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}

void Antenna::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/antenna.png");

    const int COLUMNS = 4;
    const int ROWS = 2;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.06f;

    dimensions.antennaWidth = texture.width / COLUMNS;
    dimensions.antennaHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.antennaWidth;
    drawGeometry.height = dimensions.antennaHeight;

    animation.Initialise
    (
        dimensions.antennaWidth,
        dimensions.antennaHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0,
        topOfHeadOffset
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

void Antenna::Update(float dt)
{
    Sprite::Update(dt);
}

void Antenna::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
