#include "Body/Head/Pupil.h"
#include "Constants.h"
#include <cmath>
#include <string>

Pupil::Pupil(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}

void Pupil::Initialise()
{
    Sprite::texture = LoadTexture("assets/images/TingoBingo/head/pupil.png");

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.08f;

    dimensions.pupilWidth = texture.width / COLUMNS;
    dimensions.pupilHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.pupilWidth;
    drawGeometry.height = dimensions.pupilHeight;

    animation.Initialise
    (
        dimensions.pupilWidth,
        dimensions.pupilHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );
    
    positionOffset = {0.0f, 0.0f};

    Sprite::drawGeometry.origin = {
        dimensions.pupilWidth / 2.0f,
        dimensions.pupilHeight / 2.0f
    };
}

void Pupil::Update(float dt)
{
    Sprite::Update(dt);
}

void Pupil::Draw() const
{
    Sprite::Draw();
}

void Pupil::SetPosition(Vector2 position)
{
    float radians = transform.rotation * DEG2RAD;
    float X = positionOffset.x;
    float Y = positionOffset.y;

    transform.position = {
            position.x + X * cosf(radians) - Y * sinf(radians),
            position.y + X * sinf(radians) + Y * cosf(radians)
    };
}

void Pupil::SetTransform(MyTransform parentTransform) 
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    Sprite::SetScreenCoords();
}