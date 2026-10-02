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

Headbase::Headbase(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}

// Load the head sprite and initialise its animation.
void Headbase::Initialise()
{
    Sprite::texture = LoadTexture("assets/images/TingoBingo/head/headBase.png");

    dimensions.headWidth = texture.width;
    dimensions.headHeight = texture.height;

    drawGeometry.width = texture.width;
    drawGeometry.height = texture.height;

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.02f;

    Sprite::animation.Initialise
    (
        dimensions.headWidth,
        dimensions.headHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {0.0f, 0.0f};

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    Sprite::SetShapeName("headBase");
}

void Headbase::SetTransform(MyTransform parentTransform)
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    
    Sprite::SetScreenCoords();
}
