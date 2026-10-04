#pragma once

#include "BodyDimensions.h"
#include "Shape.h"
#include <string>
#include "RobotState.h"
#include "Clamps.h"

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
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        RobotState& robotState;

        std::string side = "";

        Clamps clamps;
};