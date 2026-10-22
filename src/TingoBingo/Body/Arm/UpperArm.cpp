#include "TingoBingo/Body/Arm/UpperArm.h"
#include "raymath.h"

#include "DebugPanel.h"

UpperArm::UpperArm
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
    elbow(assets, dimensions, state, side)
{}


void UpperArm::Initialise()
{
    positionOffset = {
        0.0f,
        0.0f,
        0.0f
    };
    
    armWaveState = ArmWaveState::None;

    elbow.Initialise();
}

void UpperArm::Update(float dt)
{
    AdvanceWave(dt);
    elbow.Update(dt, armWaveState);
}

void UpperArm::Draw()
{
    DrawModelEx(
        assets.upperArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    elbow.Draw();
}

void UpperArm::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 0.0f, 1.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    elbow.SetTransform(transform);
}

void UpperArm::AdvanceWave(float dt)
{
    if(armWaveState == ArmWaveState::None)
    {
        if 
        (
            state.waveState == TingoState::WaveState::WaveLeft && 
            side == "left"
        )
        {
            armWaveState = ArmWaveState::Raising;
        }
        else if 
        (
            state.waveState == TingoState::WaveState::WaveRight && 
            side == "right"
        )
        {
            armWaveState = ArmWaveState::Raising;
        }
    }

    const float speed = 300.0f;
    const float minRotation = 0.0f;
    const float maxRotation = 135.0f;

    switch (armWaveState)
    {
        case ArmWaveState::None:
            break;
        
        case ArmWaveState::Raising:
            if
            (
                state.waveState == TingoState::WaveState::WaveLeft && 
                side == "left"
            )
            {
                localRotation += dt * speed;
                if(localRotation >= maxRotation)
                {
                    localRotation = maxRotation;
                    armWaveState = ArmWaveState::Waving;
                }
            }

            if
            (
                state.waveState == TingoState::WaveState::WaveRight && 
                side == "right"
            )
            {
                localRotation -= dt * speed;
                if(localRotation <= -maxRotation)
                {
                    localRotation = -maxRotation;
                    armWaveState = ArmWaveState::Waving;
                }
            }
            break;

        case ArmWaveState::Waving:
            if(state.waveState == TingoState::WaveState::Inactive)
            {
                armWaveState = ArmWaveState::Lowering;
            }
            break;
            
        case ArmWaveState::Lowering:
            if(side == "left")
            {
                localRotation -= dt * speed;
                if(localRotation <= minRotation)
                {
                    localRotation = minRotation;
                    armWaveState = ArmWaveState::None;
                }
            }

            if(side == "right")
            {
                localRotation += dt * speed;
                if(localRotation >= minRotation)
                {
                    localRotation = minRotation;
                    armWaveState = ArmWaveState::None;
                }
            }

            break;

        default:
            break;
    }

    SetTransform(tempParentTransform);
}

ArmWaveState UpperArm::GetWaveState() const
{
    return armWaveState;
}