#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Pupils.h"
#include "RobotState.h"

class Eyes : public Sprite
{
    public:
        Eyes(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;
        void Shutdown();

        using Sprite::Update;
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        Pupils& GetPupils();

        void LookAt(Vector2 point);
        void LookForward();

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        
        float blinkAnimationTimer = 0.0f;
        float nextBlinkAnimation = 0.0f;

        Pupils pupils;
}; 
