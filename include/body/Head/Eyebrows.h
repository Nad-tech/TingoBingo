#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Eyebrows : public Sprite
{
    public:
        Eyebrows(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;

        using Sprite::Update;
        void Update(float dt);
        
        void SetTransform(MyTransform transform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        float foreheadOffset = 65; 
};