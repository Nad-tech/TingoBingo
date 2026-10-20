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
    
    waveState = WaveState::None;

    elbow.Initialise();
}

void UpperArm::Update(float dt)
{
    AdvanceWave(dt);

    SetTransform(tempParentTransform);

    elbow.Update(dt);
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
    if(waveState == WaveState::None)
    {
        if 
        (
            state.waveState == TingoState::WaveState::WaveLeft && 
            side == "left"
        )
        {
            waveState = WaveState::Raising;
        }
        else if 
        (
            state.waveState == TingoState::WaveState::WaveRight && 
            side == "right"
        )
        {
            waveState = WaveState::Raising;
        }
    }

    const float speed = 450.0f;
    const float minRotation = 0.0f;
    const float maxRotation = 135.0f;

    switch (waveState)
    {
        case WaveState::None:
            break;
        
        case WaveState::Raising:
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
                    waveState = WaveState::Waving;
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
                    waveState = WaveState::Waving;
                }
            }
            break;

        case WaveState::Waving:
            if(state.waveState == TingoState::WaveState::Inactive)
            {
                waveState = WaveState::Lowering;
            }
            break;
            
        case WaveState::Lowering:
            if(side == "left")
            {
                localRotation -= dt * speed;
                if(localRotation <= minRotation)
                {
                    localRotation = minRotation;
                    waveState = WaveState::None;
                }
            }

            if(side == "right")
            {
                localRotation += dt * speed;
                if(localRotation >= minRotation)
                {
                    localRotation = minRotation;
                    waveState = WaveState::None;
                }
            }

            break;

        default:
            break;
    }

    SetTransform(tempParentTransform);
}

UpperArm::WaveState UpperArm::GetWaveState() const
{
    return waveState;
}