#pragma once

#include "Shape.h"
#include "RobotState.h"

class Finger : public Shape
{
    public:
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
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        RobotState& robotState;

        std::string side = "";

};