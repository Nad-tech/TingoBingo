#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "TingoBingo/Body/Head/Head.h"

class Neck
{
public:
    Neck(TingoAssets& assets,TingoDimensions& dimensions);

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;

    MyTransform3D transform;
    Vector3 positionOffset;

    Head head;
};