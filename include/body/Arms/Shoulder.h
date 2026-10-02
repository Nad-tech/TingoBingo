#pragma once 

#include "Shape.h"
#include "UpperArm.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Shoulder : public Shape
{
    public:
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
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset = {0, 0};
        RobotState& robotState;

        std::string side = "";
        UpperArm upperArm;

        std::string name;
};