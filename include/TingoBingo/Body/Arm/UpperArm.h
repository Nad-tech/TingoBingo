#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "Elbow.h"
#include "TingoBingo/TingoState.h"
class UpperArm
{
public:
    enum class WaveState
    {
        None,
        Raising,
        Lowering,
        Waving
    };

    UpperArm
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state,
        std::string side
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

    void Wave();

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;

    std::string side;

    MyTransform3D transform;
    Vector3 positionOffset;
    
    Elbow elbow;

    float localRotation = 0.0f;
    MyTransform3D tempParentTransform;

    WaveState waveState;
    void AdvanceWave(float dt);
};