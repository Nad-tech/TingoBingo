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

void Antenna::Update(float dt, Emotion emotion)
{
    Sprite::Update(dt);

    //Idle behavior
    //Wiggle the antenna at random intervals
    antennaAnimationTimer += dt;

    if (antennaAnimationTimer > nextAntennaAnimation)
    {
        animation.Play(0, 7, AnimationPriority::Idle);
        antennaAnimationTimer = 0.0f;
        nextAntennaAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Antenna::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
