#pragma once 

#include "Shape.h"
#include "UpperArm.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Shoulder : public Shape
{
    public:
        enum class ShrugState
        {
            None,
            Raising,
            Lowering,
            Shrugging
        };

        Shoulder
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

        void CloseClamp();
        void OpenClamp();
        
    private:
        void AdvanceShrug(float dt);    

        BodyDimensions& dimensions;
        Vector2 positionOffset = {0, 0};
        RobotState& robotState;

        std::string side = "";
        UpperArm upperArm;

        std::string name;

        ShrugState shrugState = ShrugState::None;
        float shrugOffsetY = 0.0f;
        MyTransform tempParentTransform;
};