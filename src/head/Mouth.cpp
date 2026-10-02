//====================================================
// Mouth.cpp
//
// Handles the robot's mouth sprite and idle animation.
// The mouth can play a simple animation to give the
// robot a more lifelike appearance.
//====================================================

#include "Body/Head/Mouth.h"
#include "Constants.h"

Mouth::Mouth(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}

// Load the mouth sprite sheet and initialise its animation.
void Mouth::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/mouth.png");

    const int COLUMNS = 3;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.5;

    dimensions.mouthWidth = texture.width / COLUMNS;
    dimensions.mouthHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.mouthWidth;
    drawGeometry.height = dimensions.mouthHeight;
    
    animation.Initialise
    (
        dimensions.mouthWidth,
        dimensions.mouthHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0,
        0
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

// Advance the mouth animation.
void Mouth::UpdateMouth(float dt)
{
    Update(dt);
}

void Mouth::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
