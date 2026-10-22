#include "TingoBingo/Body/Arm/Hand.h"
#include "raymath.h"

Hand::Hand
(
    TingoAssets& assets, 
    TingoDimensions& dimensions,
    TingoState& state
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    leftFinger(assets, dimensions, state, "left"),
    rightFinger(assets, dimensions, state, "right")
{}


void Hand::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.foreArm.height,
        0.0f
    };

    leftFinger.Initialise();
    rightFinger.Initialise();
}

void Hand::Update(float dt, ArmWaveState armWaveState)
{
    AdvanceWaveSpin(dt, armWaveState);
}

void Hand::Draw()
{
    DrawModelEx(
        assets.hand,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    leftFinger.Draw();
    rightFinger.Draw();
}

void Hand::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    leftFinger.SetTransform(transform);
    rightFinger.SetTransform(transform);
}

void Hand::AdvanceWaveSpin(float dt, ArmWaveState armWaveState)
{
    const float speed = 300;

    switch (armWaveState)
    {
    case ArmWaveState::Waving:
        localRotation += dt * speed;
        break;

    case ArmWaveState::None:
        localRotation -= dt * speed;
        if(localRotation < 0.0f)
            localRotation = 0.0f;
        break;
    
    default:
        break;
    }
}