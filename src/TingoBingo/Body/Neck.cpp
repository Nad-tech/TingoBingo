#include "TingoBingo/Body/Neck.h"
#include "raymath.h"

Neck::Neck
(
    TingoAssets& assets, 
    TingoDimensions& dimensions,
    TingoState& state
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    head(assets, dimensions, state)
{}

void Neck::Initialise()
{
    positionOffset = {
        0.0f,
        dimensions.bodyShape.height / 2.0f +
        dimensions.neck.height / 2.0f,
        0.0f
    };

    head.Initialise();

    TraceLog(LOG_INFO, "Raylib version: %s", RAYLIB_VERSION);
}

void Neck::Update(float dt)
{
    head.Update(dt);
}

void Neck::Draw()
{
    DrawModelEx(
        assets.neck,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    head.Draw();
}

void Neck::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);

    head.SetTransform(transform);
}

EyeState Neck::GetLeftEyeState() const {
    return head.GetLeftEyeState();
}

EyeState Neck::GetRightEyeState() const {
    return head.GetRightEyeState();
}

void Neck::SetGazeTarget(Vector2 target)
{
    head.SetGazeTarget(target);
}