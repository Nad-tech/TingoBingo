#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Ears : public Sprite
{
     public:
        Ears(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
};
