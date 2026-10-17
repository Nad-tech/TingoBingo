#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include <string>

class EyeBrow
{
public:
    EyeBrow
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
    
    MyTransform3D transform;

    std::string side;
};