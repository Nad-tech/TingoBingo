#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "TingoBingo/Body/Head/Head.h"
#include "TingoBingo/Body/Head/EyeState.h"
#include "TingoBingo/TingoState.h"

class Neck
{
public:
    Neck
    (
        TingoAssets& assets,
        TingoDimensions& dimensions, 
        TingoState& state
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

    EyeState GetLeftEyeState() const;
    EyeState GetRightEyeState() const;

    void SetGazeTarget(Vector2 target);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;

    MyTransform3D transform;
    Vector3 positionOffset;

    Head head;
};