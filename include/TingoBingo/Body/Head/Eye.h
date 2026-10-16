#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "TingoBingo/Body/Head/MouthDisplay.h"
#include <string>

class Eye
{
public:
    Eye(TingoAssets& assets, TingoDimensions& dimensions, std::string side);

    void Initialise();
    void ShutDown();
    
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