#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"

#include "TingoBingo/Body/Neck.h"
#include "TingoBingo/Body/Pelvis.h"
#include "TingoBingo/Body/Arm/Shoulder.h"
class Body
{
public:
    Body(TingoAssets& assets, TingoDimensions& dimensions);

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

    Pelvis pelvis;
    Neck neck;
    Shoulder leftShoulder;
    Shoulder rightShoulder;
};