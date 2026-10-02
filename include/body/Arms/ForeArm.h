#pragma once

#include "BodyDimensions.h"
#include <string>
#include "Shape.h"
#include "Hand.h"
#include "RobotState.h"
#include "WaveState.h"

class ForeArm : public Shape
{
    public:
        ForeArm(
            BodyDimensions& dimensions, 
            std::string side,
            RobotState& robotState
        );
        
        void Initialise();
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void SetWaveState(WaveState waveState);

        void WaveArm();
        
    private:
        void AdvanceWave(float dt);

        BodyDimensions& dimensions;
        Vector2 positionOffset;
        MyTransform tempParentTransform;
        
        RobotState& robotState;
        
        WaveState waveState = WaveState::None;
        float waveTimer = 0;

        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        
        std::string side = "";

        Hand hand;
};