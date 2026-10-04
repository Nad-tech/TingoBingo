#pragma once

#include "BodyDimensions.h"
#include <string>
#include "Shape.h"
#include "Hand.h"
#include "RobotState.h"

class ForeArm : public Shape
{
    public:
        enum class WaveState
        {
            None,
            Raising,
            Lowering
        };

        enum class ShrugState
        {
            None,
            Raising,
            Lowering,
            Shrugging
        };

        ForeArm(
            BodyDimensions& dimensions, 
            std::string side,
            RobotState& robotState
        );
        
        void Initialise();
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void Wave();
        void Shrug();
        
    private:
        void AdvanceWave(float dt);
        void AdvanceShrug(float dt);

        BodyDimensions& dimensions;
        Vector2 positionOffset;
        MyTransform tempParentTransform;
        
        RobotState& robotState;
        
        WaveState waveState = WaveState::None;
        float waveTimer = 0;

        ShrugState shrugState = ShrugState::None;

        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        
        std::string side = "";

        Hand hand;
};