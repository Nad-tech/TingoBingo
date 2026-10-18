#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include <string>
#include "TingoBingo/Body/Head/Pupil.h"
class Eye
{
public:
    enum class BlinkState
    {
        None,
        Closing,
        Opening
    };

    Eye
    (
        TingoAssets& assets, 
        TingoDimensions& dimensions, 
        std::string side
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

    void Blink();

private:
    TingoAssets& assets;
    TingoDimensions& dimensions;

    Vector3 positionOffset;
    
    MyTransform3D transform;

    std::string side;

    Pupil pupil;

    MyTransform3D tempParentTransform;

    BlinkState blinkState;
    Vector3 localScale;
    float blinkSpeed;

    void AdvanceBlink(float dt);
};