#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include <string>
#include "TingoBingo/Body/Arm/UpperArm.h"

class Shoulder
{
public:
    Shoulder
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions, 
        std::string side
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;

    Vector3 positionOffset;
    
    std::string side;
    
    MyTransform3D transform;

    UpperArm upperArm;

    float localRotation = 0.0f;
    bool dirFlag = false;
};