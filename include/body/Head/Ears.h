#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Emotion.h"

class Ears : public Sprite
{
     public:
        Ears(BodyDimensions& dimensions);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt, Emotion emotion);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0;
};
