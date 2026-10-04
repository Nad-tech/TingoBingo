#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class EyeBrow : public Sprite
{
    public:
        EyeBrow(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        
        void Initialise() override;

        using Sprite::Update;
        void Update(float dt);

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        std::string side;
}; 
