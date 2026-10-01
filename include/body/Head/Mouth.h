#pragma once

#include "Sprite.h"
#include "Emotion.h"
#include "BodyDimensions.h"

class Mouth : public Sprite
{
    public:
        Mouth(BodyDimensions& dimensions);
        
        void Initialise() override;
        void UpdateMouth(float dt, Emotion emotion);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        float mouthDisplayOffset = 28.0f;
};