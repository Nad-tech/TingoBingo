#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Pupils.h"
#include "Emotion.h"

class Eyes : public Sprite
{
    public:
        Eyes(BodyDimensions& dimensions);
        
        void Initialise() override;
        void Shutdown();

        using Sprite::Update;
        void Update(float dt, Emotion emotion);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        Pupils& GetPupils();

        void LookAt(Vector2 point);
        void LookForward();

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        float blinkAnimationTimer = 0.0f;
        float nextBlinkAnimation = 0.0f;

        Pupils pupils;
}; 
