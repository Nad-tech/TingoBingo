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

    const int COLUMNS = 4;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;

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
        -55.0f + dimensions.headHeight / 2.0f
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

// Advance the mouth animation.
void Mouth::Update(float dt)
{
    Sprite::Update(dt);

    if (robotState.emotion == RobotState::Emotions::Happy && !robotState.speaking)
    {
        frame = 0;
        frameTimer = 0.0f;
        animation.SetFrame(frame);
        return;
    }

    if (!robotState.speaking)
    {
        frame = 1;
        frameTimer = 0.0f;
        animation.SetFrame(frame);
        return;
    }

    frameTimer += dt;

    if (frameTimer >= FRAME_DURATION)
    {
        frameTimer -= FRAME_DURATION;
        frame = (frame == 1) ? 2 : 1;
        animation.SetFrame(frame);
    }

    
}

void Mouth::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
