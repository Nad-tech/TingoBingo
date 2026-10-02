#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Headbase : public Sprite 
{
    public:
        Headbase(BodyDimensions& dimensions, RobotState& robotState);
        void Initialise() override;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        std::string name = "headBase";
};
