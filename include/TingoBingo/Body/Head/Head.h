#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "TingoBingo/Body/Head/MouthDisplay.h"
#include "TingoBingo/Body/Head/Eye.h"
#include "TingoBingo/Body/Head/Nose.h"
#include "TingoBingo/Body/Head/EyeBrow.h"
#include "TingoBingo/Body/Head/Ear.h"
#include "TingoBingo/Body/Head/Antenna.h"
#include "TingoBingo/TingoState.h"

class Head
{
public:
    Head
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

    Vector3 positionOffset;
    
    MyTransform3D transform;

    MouthDisplay mouthDisplay;
    Eye leftEye;
    Eye rightEye;
    Nose nose;
    EyeBrow leftEyeBrow;
    EyeBrow rightEyeBrow;
    Ear leftEar;
    Ear rightEar;
    Antenna antenna;

    float localRotation = 0.0f;

    float blinkTimer = 0.0f;
    float nextBlink = 0.0f;
};