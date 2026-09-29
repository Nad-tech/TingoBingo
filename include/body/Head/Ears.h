#pragma once

#include "Shape.h"
#include "BodyDimensions.h"

class Ears : public Shape
{
     public:
        Ears(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt);
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0;
};
