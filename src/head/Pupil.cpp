#include "Body/Head/Pupil.h"
#include "Constants.h"
#include <cmath>
#include <string>
#include "raymath.h"

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

    // Smoothly move the pupil towards its target.
    float smoothing = 1.0f - expf(-lookSpeed * dt);

    lookOffset.x += (targetLookOffset.x - lookOffset.x) * smoothing;
    lookOffset.y += (targetLookOffset.y - lookOffset.y) * smoothing;
}

void Pupil::Draw() const
{
    Sprite::Draw();
}

void Pupil::SetTransform(MyTransform parentTransform) 
{
    tempParentTransform = parentTransform;

    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    
    float radians = parentTransform.rotation * DEG2RAD;

    Vector2 rotatedOffset = {
        lookOffset.x * cosf(radians) - lookOffset.y * sinf(radians),
        lookOffset.x * sinf(radians) + lookOffset.y * cosf(radians)
    };

    Sprite::transform.position.x += rotatedOffset.x;
    Sprite::transform.position.y += rotatedOffset.y;
    
    Sprite::SetScreenCoords();
}

void Pupil::LookAt(Vector2 point)
{
    const float MAX_LOOK_DISTANCE = 15.0f;

    Vector2 direction = {
        point.x - transform.position.x,
        point.y - transform.position.y
    };

    float distance = Vector2Length(direction);

    if (distance > 0.0f)
    {
        direction = Vector2Scale(direction, 1.0f / distance);

        float movement = fminf(distance, MAX_LOOK_DISTANCE);

        targetLookOffset = Vector2Scale(direction, movement);
    }
    else
    {
        targetLookOffset = { 0.0f, 0.0f };
    }
}