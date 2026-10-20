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

void ForeArm::Update(float dt)
{
    if(waveState != WaveState::None)
    {
        AdvanceWave(dt);
    }

    SetTransform(tempParentTransform);

    hand.Update(dt);
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

void ForeArm::Wave()
{
    if(waveState == WaveState::None)
    {
        waveState = WaveState::Raising;
    }
}

void ForeArm::AdvanceWave(float dt)
{
    // if(side == "left")
    // {
    //     const float speed = 400.0f;
    //     const float minRotation = 0.0f;
    //     const float maxRotation = 70.0f;
        
    //     if(waveState == WaveState::Raising)
    //     {
    //         localRotation += speed * dt;
            
    //         if(localRotation >= maxRotation)
    //         {
    //             localRotation = maxRotation;
    //             waveState = WaveState::Lowering;
    //         }
    //     }
    //     else if(waveState == WaveState::Lowering)
    //     {
    //         localRotation -= speed * dt;

    //         if(localRotation <= minRotation)
    //         {
    //             localRotation = minRotation;
                
    //             if(state.gestures.waveLeft)
    //             {
    //                 waveState = WaveState::Raising;
    //             }
    //             else {
    //                 waveState = WaveState::None;
    //             }
    //         }
    //     }
    // }

    // if(side == "right")
    // {
    //     const float speed = 400.0f;
    //     const float minRotation = 0.0f;
    //     const float maxRotation = -70.0f;

    //     if(waveState == WaveState::Raising)
    //     {
    //         localRotation -= speed * dt;
            
    //         if(localRotation <= maxRotation)
    //         {
    //             localRotation = maxRotation;
    //             waveState = WaveState::Lowering;
    //         }
    //     }
    //     else if(waveState == WaveState::Lowering)
    //     {
    //         localRotation += speed * dt;

    //         if(localRotation >= minRotation)
    //         {
    //             localRotation = minRotation;
                
    //             if(state.gestures.waveRight)
    //             {
    //                 waveState = WaveState::Raising;
    //             }
    //             else {
    //                 waveState = WaveState::None;
    //             }
    //         }
    //     }
    // }

    SetTransform(tempParentTransform);
}
