#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "Finger.h"
#include "TingoBingo/TingoState.h"
class Hand
{
public:
    Hand
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;

    Vector3 positionOffset;
    MyTransform3D transform;

    Finger leftFinger;
    Finger rightFinger;

    float localRotation = 0.0f;
    MyTransform3D tempParentTransform;
    bool dirFlag = false;
};