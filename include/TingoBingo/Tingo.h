#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/Body/Body.h"
#include "TingoDimensions.h"
#include "TingoAssets.h"

class Tingo
{
public:
    Tingo(TingoAssets& assets, TingoDimensions& dimensions);
    
    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D initialTransform);

private:
    MyTransform3D transform;
    TingoAssets &assets;
    TingoDimensions& dimensions;
    Body body;
};