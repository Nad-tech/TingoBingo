#pragma once

#include "Shape.h"
#include "BodyDimensions.h"
#include "Pupils.h"

class Eyes : public Shape
{
    public:
        Eyes(BodyDimensions& dimensions);
        
        void Initialise() override;
        void Shutdown();

        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        Pupils& GetPupils();

        void LookAt(Vector2 point);
        void LookForward();

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        Pupils pupils;

        // TODO: make pupils child of Eyes
        float idleAnimationTimer = 0.0f;
        float nextIdleAnimation = 0.0f;
}; 
