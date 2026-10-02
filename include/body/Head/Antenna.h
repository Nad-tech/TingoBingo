#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Antenna : public Sprite 
{
    public:
        Antenna(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        
        float topOfHeadOffset = 46.0f;
};
