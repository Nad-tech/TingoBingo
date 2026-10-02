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

        void WaveArm(float dt);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        MyTransform tempParentTransform;
        
        RobotState& robotState;
        
        WaveState waveState = WaveState::None;

        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        
        std::string side = "";

        Hand hand;
};