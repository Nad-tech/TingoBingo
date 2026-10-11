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
    // Limit how far the pupil can move from its resting position.
    const float MAX_LOOK_DISTANCE = 15.0f;

    // Calculate the direction and distance from the pupil to the target.
    Vector2 direction =
    {
        point.x - transform.position.x,
        point.y - transform.position.y
    };

    // Calculate the distance to the target using the direction vector's length.
    float distance = Vector2Length(direction);

    if (distance > 0.0f)
    {
        // Normalize the direction so its length is 1, independent of distance.
        direction = Vector2Scale(direction, 1.0f / distance);

        // Move towards the target, but never farther than MAX_LOOK_DISTANCE.
        float movement = fminf(distance, MAX_LOOK_DISTANCE);

        // Calculate the final offset in the target's direction.
        lookOffset = Vector2Scale(direction, movement);
    }
    else
    {
        // The target is at the pupil's position, so no movement is needed.
        lookOffset = { 0.0f, 0.0f };
    }
    
    SetTransform(tempParentTransform);
}