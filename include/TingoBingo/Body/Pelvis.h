#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/Body/Leg/Thigh.h"
#include "TingoBingo/TingoAssets.h"

class Pelvis
{
public:
    Pelvis(TingoAssets& assets, TingoDimensions& dimensions);

    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    MyTransform3D transform;
    
    Vector3 positionOffset;

    Thigh leftThigh;
    Thigh rightThigh;
};