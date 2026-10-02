#include "Body/Head/Eyebrows.h"
#include "Constants.h"

Eyebrows::Eyebrows(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}

void Eyebrows::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/eyebrows.png");

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.3f;

    dimensions.eyeBrowsWidth = texture.width / COLUMNS;
    dimensions.eyeBrowsHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.eyeBrowsWidth;
    drawGeometry.height = dimensions.eyeBrowsHeight;

    animation.Initialise
    (
        dimensions.eyeBrowsWidth,
        dimensions.eyeBrowsHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0,
        foreheadOffset
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

void Eyebrows::Update(float dt)
{
    Sprite::Update(dt);
}

void Eyebrows::SetTransform(MyTransform parentTransform) 
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
