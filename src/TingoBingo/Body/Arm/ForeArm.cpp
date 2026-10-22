#include "TingoBingo/Body/Arm/ForeArm.h"
#include "raymath.h"

ForeArm::ForeArm
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
    hand(assets, dimensions, state)
{}


void ForeArm::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.elbow.height / 2.0f,
        0.0f
    };

    waveState = WaveState::None;

    hand.Initialise();
}

void ForeArm::Update(float dt, ArmWaveState armWaveState)
{
    AdvanceWave(dt, armWaveState);
    hand.Update(dt, armWaveState);
}

void ForeArm::Draw()
{
    DrawModelEx(
        assets.foreArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    hand.Draw();
}

void ForeArm::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 0.0f, 1.0f};
    localTransform.rotationAngle += localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    hand.SetTransform(transform);
}

void ForeArm::AdvanceWave(float dt, ArmWaveState armWaveState)
{
    const float speed = 450.0f;
    const float minRotation = 0.0f;
    const float maxRotation = 60.0f;
    const float restingRotation = 0.0f;

    switch (armWaveState)
    {
    case ArmWaveState::Waving:
        switch (waveState)
        {
            case WaveState::None:
                waveState = WaveState::Raising;
                
                break;

            case WaveState::Raising:
                if(side == "left")
                {
                    localRotation += dt * speed;
                    
                    if(localRotation >= maxRotation)
                        waveState = WaveState::Lowering;
                }
                else if(side == "right")
                {
                    localRotation -= dt * speed;
                    
                    if(localRotation <= -maxRotation)
                        waveState = WaveState::Lowering;
                }
                break;

            case WaveState::Lowering:
                if(side == "left")
                {
                    localRotation -= dt * speed;
                    
                    if(localRotation <= minRotation)
                        waveState = WaveState::Raising;
                }
                else if(side == "right")
                {
                    localRotation += dt * speed;
                    
                    if(localRotation >= -minRotation)
                        waveState = WaveState::Raising;
                }

                break;

            default:
                break;
        }

        break;
        
    case ArmWaveState::None:
    {
        const float returnSpeed = 180.0f;

        if (localRotation > restingRotation)
        {
            localRotation -= dt * returnSpeed;

            if (localRotation < restingRotation)
                localRotation = restingRotation;
        }
        else if (localRotation < restingRotation)
        {
            localRotation += dt * returnSpeed;

            if (localRotation > restingRotation)
                localRotation = restingRotation;
        }

        if (localRotation == restingRotation)
            waveState = WaveState::None;

        break;
    }

    default:
        break;
    }

    SetTransform(tempParentTransform);
}
