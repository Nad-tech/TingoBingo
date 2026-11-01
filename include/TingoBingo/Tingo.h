#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/Body/Body.h"
#include "TingoDimensions.h"
#include "TingoAssets.h"
#include "TingoBingo/TingoState.h"
#include "TingoBingo/TingoBrain.h"
#include "TingoBingo/TingoVision.h"

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

    EyeState GetLeftEyeState() const;
    EyeState GetRightEyeState() const;

    MyTransform3D& GetTransform();

    void SetGazeTarget(Vector2 target);

    void UpdateVision(
    Vector3 observerPosition,
        const std::vector<GameObject*>& objects
    );

    const std::vector<GameObject*>& GetVisibleObjects() const;

private:
    MyTransform3D transform;
    TingoAssets &assets;
    TingoDimensions& dimensions;
    TingoState state;
    Body body;
    TingoBrain tingoBrain;
    TingoVision vision;
};