#pragma once
#include "BodyDimensions.h"
#include "Shape.h"
#include "Foot.h"
#include "RobotState.h"
#include <string>

class Shin : public Shape
{
    public:
        enum class CrouchState
        {
            None,
            Raising,
            Crouching,
            Returning
        };


        Shin(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTrnsform);

        void Crouch();

    private:
        void AdvanceCrouch(float dt);

        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        std::string side;

        Foot foot;

        CrouchState crouchState = CrouchState::None;
        MyTransform tempParentTransform;
        float localRotation = 0.0f;
};