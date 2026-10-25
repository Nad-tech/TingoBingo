#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"
#include "Animation.h"
#include "TingoBingo/TingoState.h"

class MouthDisplay
{
public:
    MouthDisplay(
        TingoAssets& assets, 
        TingoDimensions& dimensions,
        TingoState& state
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D parentTransform);

    void SetMouthFrame(int frame);

    void ShutDown();
private:
    TingoAssets& assets;
    TingoDimensions& dimensions;
    TingoState& state;


    Vector3 positionOffset;
    
    MyTransform3D transform;

    Animation animation;

    Model mouthPlane{};
    MyTransform3D mouthPlaneTransform{};
    Vector3 mouthPlaneOffset;

    void AdvanceSpeakAnimation();
};