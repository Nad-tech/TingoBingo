#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "Hand.h"

class ForeArm
{
public:
    ForeArm(TingoAssets& assets, TingoDimensions& dimensions);

    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;

    Vector3 positionOffset;
    
    std::string side;
    
    MyTransform3D transform;

    Hand hand;
};