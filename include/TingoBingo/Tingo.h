#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/Body/Body.h"
#include "TingoDimensions.h"
#include "TingoAssets.h"
#include "TingoBingo/TingoState.h"
#include "TingoBingo/TingoBrain.h"

class Tingo
{
public:
    Tingo(TingoAssets& assets, TingoDimensions& dimensions);
    
    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D initialTransform);

    TingoState& GetState();

    ArmWaveState GetLeftArmWaveState() const;
    ArmWaveState GetRightArmWaveState() const;

private:
    MyTransform3D transform;
    TingoAssets &assets;
    TingoDimensions& dimensions;
    TingoState state;
    Body body;
    TingoBrain tingoBrain;
};