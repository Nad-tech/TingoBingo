#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "Hand.h"
#include "TingoBingo/TingoState.h"
#include "TingoBingo/Body/Arm/ArmWaveState.h"

class ForeArm
{
public:
    enum class WaveState
    {
        None,
        Raising,
        Lowering
    };

    ForeArm
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state,
        std::string side
    );

    void Initialise();
    
    void Update(float dt, ArmWaveState armWaveState);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;

    std::string side;

    Vector3 positionOffset;
    MyTransform3D transform;

    Hand hand;

    float localRotation = 0.0f;
    MyTransform3D tempParentTransform;

    void AdvanceWave(float dt, ArmWaveState armWaveState);
    WaveState waveState;
};