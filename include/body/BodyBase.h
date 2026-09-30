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
        Vector2 positionOffset;
        Vector2 globalPivot = {0, 0};

        std::string shapeName = "BodyBase"; 
};
