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
    
    void Update(float dt, const std::vector<GameObject*>& gameObjects);
    void Draw();

    void SetTransform(MyTransform3D initialTransform);

    TingoState& GetState();

    ArmWaveState GetLeftArmWaveState() const;
    ArmWaveState GetRightArmWaveState() const;

    EyeState GetLeftEyeState() const;
    EyeState GetRightEyeState() const;

    MyTransform3D& GetTransform();

    void SetGazeTarget(Vector2 target);

    void UpdateVision(const std::vector<GameObject*>& objects);

    const std::vector<GameObject*>& GetVisibleObjects() const;

    Vector3 GetVisionPosition() const;
    Vector3 GetHeadForwardDirection() const;

private:
    MyTransform3D transform;
    TingoAssets &assets;
    TingoDimensions& dimensions;
    TingoState state;
    Body body;
    TingoBrain tingoBrain;
    TingoVision vision;
};