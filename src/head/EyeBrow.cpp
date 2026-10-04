#include "Body\Head\EyeBrow.h"

EyeBrow::EyeBrow(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    side(side)
{}
        
void EyeBrow::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/eyeBrow.png");

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.02f;

    dimensions.eyeBrowWidth = texture.width / COLUMNS;
    dimensions.eyeBrowHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.eyeBrowWidth;
    drawGeometry.height = dimensions.eyeBrowHeight;


    Sprite::animation.Initialise
    (
        dimensions.eyeWidth,
        dimensions.eyeHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = { side == "left" ? 40.0f : -40.0f , 70.0f };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

void EyeBrow::Update(float dt)
{
    Sprite::Update(dt);
}

void EyeBrow::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
