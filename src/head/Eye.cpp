#include "Body\Head\Eye.h"

Eye::Eye(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    side(side),
    pupil(dimensions, robotState)
{}

void Eye::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/eye.png");

    const int COLUMNS = 5;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.02f;

    dimensions.eyeWidth = texture.width / COLUMNS;
    dimensions.eyeHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.eyeWidth;
    drawGeometry.height = dimensions.eyeHeight;


    Sprite::animation.Initialise
    (
        dimensions.eyeWidth,
        dimensions.eyeHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = { side == "left" ? 40.0f : -40.0f , 40.0f };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    pupil.Initialise();
}

void Eye::ShutDown()
{
    Sprite::ShutDown();
}

void Eye::Update(float dt)
{
    Sprite::Update(dt);
}

void Eye::Draw() const
{
    Sprite::Draw();
    pupil.Draw();
}

void Eye::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();

    pupil.SetTransform(transform);
}

void Eye::Blink()
{
    animation.Play(0, 4, AnimationPriority::Idle);
}