#pragma once

#include "BodyDimensions.h"
#include "Shape.h"
#include <string>
#include "RobotState.h"
#include "Clamp.h"

class Hand : public Shape
{
    public:
        Hand
        (
            BodyDimensions& dimensions, 
            std::string side,
            RobotState& robotState
        );
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void CloseClamp();
        void OpenClamp();
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        RobotState& robotState;

        std::string side = "";

        Clamp clamp;
};