#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/Body/Leg/Thigh.h"
#include "TingoBingo/TingoAssets.h"

class Legs
{
public:
    Legs(TingoAssets& assets,TingoDimensions& dimensions);

    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;

    Thigh leftThigh;
    Thigh rightThigh;
};