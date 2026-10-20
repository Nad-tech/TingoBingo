#include "TingoBingo/Body/Body.h"

Body::Body
(
    TingoAssets& assets, 
    TingoDimensions& dimensions, 
    TingoState& state
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    pelvis(assets, dimensions),
    neck(assets, dimensions),
    leftShoulder(assets, dimensions, state, "left"),
    rightShoulder(assets, dimensions, state, "right")
{}

void Body::Initialise()
{
    positionOffset = {0.0f, 0.0f, 0.0f};

    pelvis.Initialise();
    neck.Initialise();
    leftShoulder.Initialise();
    rightShoulder.Initialise();
}

void Body::Update(float dt)
{
    pelvis.Update(dt);
    neck.Update(dt);
    leftShoulder.Update(dt);
    rightShoulder.Update(dt);
}

void Body::Draw()
{
    DrawModelEx(
        assets.body,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    pelvis.Draw();
    neck.Draw();
    leftShoulder.Draw();
    rightShoulder.Draw();
}

void Body::SetTransform(MyTransform3D parentTransform)
{   
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    pelvis.SetTransform(transform);
    neck.SetTransform(transform);
    leftShoulder.SetTransform(transform);
    rightShoulder.SetTransform(transform);
}

UpperArm::WaveState Body::GetLeftArmWaveState() const
{
    return leftShoulder.GetWaveState();
}

UpperArm::WaveState Body::GetRightArmWaveState() const
{
    return rightShoulder.GetWaveState();
}