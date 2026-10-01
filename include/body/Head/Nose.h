#pragma once

#include "Sprite.h"
#include "raylib.h"
#include "BodyDimensions.h"
#include "Emotion.h"

class Nose : public Sprite
{
    public:
        Nose(BodyDimensions& dimensions);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt, Emotion emotion);
        void Draw() const override;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        float slightPositionOffset = 5.0f;
}; 


