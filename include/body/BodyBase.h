#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

#include <string>

class BodyBase : public Sprite 
{
    public:
        BodyBase(BodyDimensions& dimensions);
        void Initialise() override;

        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset = { 0.0f, 0.0f };

        std::string shapeName = "BodyBase"; 
};
