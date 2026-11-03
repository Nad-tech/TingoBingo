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
    const MyTransform3D& GetTransform() const;

    EyeState GetLeftEyeState() const;
    EyeState GetRightEyeState() const;

    void SetGazeTarget(Vector2 target);

    Vector3 GetVisionPosition() const;
    Vector3 GetForwardDirection() const;

    void SetLocalYaw(float yaw);
    float GetLocalYaw();

    void SetLocalPitch(float pitch);
    float GetLocalPitch();

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

    float localYaw = 0.0f;
    float localPitch = 0.0f;

    float blinkTimer = 0.0f;
    float nextBlink = 0.0f;
};