#pragma once

#include "Shape.h"
#include "Knee.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
#include "RobotState.h"

#include <string>

class Thigh : public Shape
{
    public:
        Thigh(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        
        std::string side;
        
        Knee knee;
};