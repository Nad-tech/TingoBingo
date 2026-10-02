#pragma once

#include "BodyDimensions.h"
#include "Shape.h"
#include "RobotState.h"
#include <string>

class Foot : public Shape
{
    public:
        Foot(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        
        void Initialise() override;
        void Update(float dt);
        
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        std::string side;
};