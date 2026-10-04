#include "Body/Head/Ear.h"
#include "Constants.h"

Ear::Ear(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    side(side)

{}

void Ear::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/ear.png");
    
    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.09f;

    dimensions.earWidth = texture.width / COLUMNS;
    dimensions.earHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.earWidth;
    drawGeometry.height = dimensions.earHeight;

    animation.Initialise
    (
        dimensions.earWidth,
        dimensions.earHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {side == "left" ? 110.0f : -110.0f, 0};

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

void Ear::Update(float dt)
{
    Sprite::Update(dt);
}

void Ear::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
