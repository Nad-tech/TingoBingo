#include "TingoBingo/Body/Head/Pupil.h"
#include "raymath.h"

Pupil::Pupil(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Pupil::Initialise()
{
    positionOffset = {
        0.0f,
        0.0f,
        dimensions.eye.length / 2.0f
        + dimensions.pupil.length / 2.0f
    };

    gazeSpeed = 0.9f;

    // Leave room for the pupil to move without leaving the eye.
    const float safetyMargin = 0.7f;

    maxGazeX = (
        dimensions.eye.width - dimensions.pupil.width
    ) / 2.0f * safetyMargin;

    maxGazeY = (
        dimensions.eye.height - dimensions.pupil.height
    ) / 2.0f * safetyMargin;

    gazeOffset = {0.0f, 0.0f};
    targetGazeOffset = {0.0f, 0.0f};
}

void Pupil::Update(float dt)
{
    // Exponential smoothing makes movement consistent
    // across different frame rates.
    float smoothing = 1.0f - expf(-gazeSpeed * dt);

    gazeOffset.x +=
        (targetGazeOffset.x - gazeOffset.x) * smoothing;

    gazeOffset.y +=
        (targetGazeOffset.y - gazeOffset.y) * smoothing;
}

void Pupil::Draw()
{
    DrawModelEx(
        assets.pupil,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void Pupil::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = {
        positionOffset.x + gazeOffset.x,
        positionOffset.y + gazeOffset.y,
        positionOffset.z
    };

    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}

void Pupil::SetGazeTarget(Vector2 target)
{
    targetGazeOffset.x = Clamp(
        target.x,
        -maxGazeX,
        maxGazeX
    );

    targetGazeOffset.y = Clamp(
        target.y,
        -maxGazeY,
        maxGazeY
    );
}