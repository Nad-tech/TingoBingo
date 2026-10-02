#pragma once

#include "Sprite.h"
#include "raylib.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Nose : public Sprite
{
    public:
        Nose(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt);
        void Draw() const override;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        
        float slightPositionOffset = 5.0f;
}; 


