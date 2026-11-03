#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/Body/Leg/Thigh.h"
#include "TingoBingo/TingoAssets.h"
#include "TingoBingo/TingoState.h"

class Pelvis
{
public:
    Pelvis
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

    void SetLeftThighLocalRotation(float angle);
    void SetRightThighLocalRotation(float angle);

    float GetLeftThighLocalRotation();
    float GetRightThighLocalRotation();

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;
    MyTransform3D transform;
    
    Vector3 positionOffset;

    Thigh leftThigh;
    Thigh rightThigh;

    float localRotation;
    MyTransform3D tempParentTransform;
};