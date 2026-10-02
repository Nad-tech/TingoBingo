#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Mouth : public Sprite
{
    public:
        Mouth(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;
        void UpdateMouth(float dt);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        
        float mouthDisplayOffset = 28.0f;
};