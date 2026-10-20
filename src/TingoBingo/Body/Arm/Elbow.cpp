#include "TingoBingo/Body/Arm/Elbow.h"
#include "raymath.h"

Elbow::Elbow
(
    TingoAssets& assets, 
    TingoDimensions& dimensions,
    TingoState& state,
    std::string side
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    side(side),
    foreArm(assets, dimensions, state, side)
{}

void Elbow::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.upperArm.height - dimensions.elbow.height / 2.0f, 
        0.0f
    };

    foreArm.Initialise();
}

void Elbow::Update(float dt, ArmWaveState armWaveState)
{
    foreArm.Update(dt, armWaveState);
}

void Elbow::Draw()
{
    DrawModelEx(
        assets.elbow,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    foreArm.Draw();
}

void Elbow::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    foreArm.SetTransform(transform);
}