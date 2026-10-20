#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "Elbow.h"
#include "TingoBingo/TingoState.h"
#include "TingoBingo/Body/Arm/ArmWaveState.h"
class UpperArm
{
public:
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

    ArmWaveState GetWaveState() const;
    
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

    ArmWaveState armWaveState;
    void AdvanceWave(float dt);
};