#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Pupil.h"
#include "RobotState.h"

class Eye : public Sprite
{
    public:
        Eye(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        
        void Initialise() override;
        void Shutdown();

        using Sprite::Update;
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        
        float blinkAnimationTimer = 0.0f;
        float nextBlinkAnimation = 0.0f;

        Pupil pupil;
}; 
