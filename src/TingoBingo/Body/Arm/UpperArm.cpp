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
    if(waveState != WaveState::None)
    {
        AdvanceWave(dt);
    }

    SetTransform(tempParentTransform);

    elbow.Update(dt);

    std::string state = "";
    switch (waveState)
    {
    case WaveState::None :
        state = "None";
        break;
    
    case WaveState::Lowering :
        state = "Lowering";
        break;
    
    case WaveState::Raising :
        state = "Raising";
        break;
    
    case WaveState::Waving :
        state = "Waving";
        break;
        
    default:
        state = "NULL";
        break;
    }

    if(side == "left")
        DebugPanel::Instance().Print("WaveState: ", state);

    /*if(side == "right")
        DebugPanel::Instance().Print("WaveState: ", state);*/
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

void UpperArm::Wave()
{
    if(waveState == WaveState::None)
    {
        waveState = WaveState::Raising;
    }
}

void UpperArm::AdvanceWave(float dt)
{
    const float speed = 450.0f;
    const float minRotation = 0.0f;
    const float maxRotation = 135.0f;

    if(side == "left")
    {
        if(waveState == WaveState::Raising)
        {
            localRotation += speed * dt;
            
            if(localRotation >= maxRotation)
            {
                localRotation = maxRotation;
                waveState = WaveState::Waving;
                elbow.Wave();
            }
        }
        else if(waveState == WaveState::Waving)
        {
            if(!state.gestures.waveLeft)
            {
                waveState = WaveState::Lowering;
            }
        }
        else if(waveState == WaveState::Lowering)
        {
            localRotation -= speed * dt;

            if(localRotation <= minRotation)
            {
                localRotation = minRotation;
                waveState = WaveState::None;
            }
        }
    }

    if(side == "right")
    {
        if(waveState == WaveState::Raising)
        {
            localRotation -= speed * dt;
            
            if(localRotation <= -maxRotation)
            {
                localRotation = -maxRotation;
                waveState = WaveState::Waving;
                elbow.Wave();
            }
        }
        else if(waveState == WaveState::Waving)
        {
            if(!state.gestures.waveRight)
            {
                waveState = WaveState::Lowering;
            }
        }
        else if(waveState == WaveState::Lowering)
        {
            localRotation += speed * dt;

            if(localRotation >= -minRotation)
            {
                localRotation = -minRotation;
                waveState = WaveState::None;
            }
        }
    }

    SetTransform(tempParentTransform);
}