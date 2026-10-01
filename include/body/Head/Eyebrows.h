#pragma once

#include "Sprite.h"
#include "Emotion.h"
#include "BodyDimensions.h"

class Eyebrows : public Sprite
{
    public:
        Eyebrows(BodyDimensions& dimensions);
        
        void Initialise() override;

        using Sprite::Update;
        void Update(float dt, Emotion emotion);
        
        void SetTransform(MyTransform transform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        float foreheadOffset = 65; 
};