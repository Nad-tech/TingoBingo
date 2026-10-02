#pragma once

#include "Shape.h"
#include "ForeArm.h"
#include "BodyDimensions.h"
#include <string>
#include "RobotState.h"

class Elbow : public Shape
{
    public:
        Elbow
        (
            BodyDimensions& dimensions,
            std::string side,
            RobotState& robotState
        );
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        void WaveArm();

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        RobotState& robotState;

        WaveState waveState = WaveState::None;

        std::string side = "";

        ForeArm foreArm;
};