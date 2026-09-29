#pragma once

#include "Shape.h"
#include "BodyDimensions.h"

class Headbase : public Shape 
{
    public:
        Headbase(BodyDimensions& dimensions);
        void Initialise() override;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
};
