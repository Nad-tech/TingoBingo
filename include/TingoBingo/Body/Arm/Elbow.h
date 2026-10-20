#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "TingoBingo/Body/Arm/ForeArm.h"
#include "TingoBingo/TingoState.h"
class Elbow
{
public:
    Elbow
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state,
        std::string side
    );

    void Initialise();
    
    void Update(float dt, ArmWaveState waveState);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;

    std::string side;

    Vector3 positionOffset;
    MyTransform3D transform;

    ForeArm foreArm;
};