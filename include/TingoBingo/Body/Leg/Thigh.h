#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include <string>
#include "TingoBingo/TingoAssets.h"
#include "Knee.h"

class Thigh
{
public:
    Thigh
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
    MyTransform3D transform;

    Vector3 positionOffset;

    std::string side;

    Knee knee;
};