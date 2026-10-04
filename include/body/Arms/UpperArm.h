#pragma once
#include <string>
#include "Shape.h"
#include "Body/Arms/Elbow.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class UpperArm : public Shape
{
    public:
        enum class WaveState
        {
            None,
            Raising,
            Lowering,
            Waving
        };

        enum class ShrugState
        {
            None,
            Raising,
            Lowering,
            Shrugging
        };

        UpperArm
        (
            BodyDimensions& dimensions, 
            std::string side, 
            RobotState& robotState
        );

        void Initialise() override;
     
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
        ShrugState shrugState = ShrugState::None;

        float localRotation = 0.0f;
        
        std::string side = "";

        Elbow elbow;
};
