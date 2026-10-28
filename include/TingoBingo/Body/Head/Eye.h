#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include <string>
#include "TingoBingo/Body/Head/Pupil.h"
#include "TingoBingo/Body/Head/EyeState.h"
#include "TingoBingo/TingoState.h"
class Eye
{
public:
    Eye
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state, 
        std::string side
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

    EyeState GetEyeState() const;

    void SetGazeTarget(Vector2 target);

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;

    Vector3 positionOffset;
    
    MyTransform3D transform;

    std::string side;

    Pupil pupil;

    MyTransform3D tempParentTransform;

    EyeState eyeState;

    Vector3 localScale;
    void AdvanceBlink(float dt);
};