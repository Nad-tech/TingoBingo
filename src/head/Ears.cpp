#include "Body/Head/Ears.h"
#include "Constants.h"

Ears::Ears(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}

void Ears::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/ears.png");
    
    const int COLUMNS = 5;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.09f;

    dimensions.earsWidth = texture.width / COLUMNS;
    dimensions.earsHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.earsWidth;
    drawGeometry.height = dimensions.earsHeight;

    animation.Initialise
    (
        dimensions.earsWidth,
        dimensions.earsHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {0, 0};

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

void Ears::Update(float dt)
{
    Sprite::Update(dt);
}

void Ears::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
