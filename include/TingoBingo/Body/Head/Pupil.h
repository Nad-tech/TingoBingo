#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include <string>

class Pupil
{
public:
    Pupil(TingoAssets& assets, TingoDimensions& dimensions);

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;

    Vector3 positionOffset;
    
    MyTransform3D transform;
};