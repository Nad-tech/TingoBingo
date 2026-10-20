#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include <string>
#include "TingoBingo/Body/Arm/UpperArm.h"
#include "TingoBingo/TingoState.h"

class Shoulder
{
public:
    Shoulder
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

    UpperArm::WaveState GetWaveState() const;

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;
    
    std::string side;
    
    MyTransform3D transform;
    Vector3 positionOffset;
    
    UpperArm upperArm;

    float localRotation = 0.0f;
    bool dirFlag = false;
};