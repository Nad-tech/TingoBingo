#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
class BodyBase : public Sprite 
{
    public:
        BodyBase(BodyDimensions& dimensions);
        void Initialise() override;

        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
};
