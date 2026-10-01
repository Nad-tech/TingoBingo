#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Emotion.h"

class Antenna : public Sprite 
{
    public:
        Antenna(BodyDimensions& dimensions);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt, Emotion emotion);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        float antennaAnimationTimer = 0.0f;
        float nextAntennaAnimation = 3.0f;
        float topOfHeadOffset = 46.0f;
};
