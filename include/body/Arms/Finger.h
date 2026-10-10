#pragma once

#include "Shape.h"
#include "RobotState.h"

class Finger : public Shape
{
    public:
        enum class FingerState
        {
            Open,
            Close,
        };

        Finger
        (
            BodyDimensions& dimensions, 
            std::string side,
            RobotState& robotState
        );
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void Open();
        void Close();
        
    private:
        void AdvanceOpenClose(float dt);

        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        RobotState& robotState;

        std::string side = "";

        MyTransform tempParentTransform;

        float localRotation = 0.0f;

        FingerState state = FingerState::Open;
};