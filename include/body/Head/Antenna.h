#pragma once

#include "Shape.h"
#include "BodyDimensions.h"

class Antenna : public Shape 
{
    public:
        Antenna(BodyDimensions& dimensions);
        
        void Initialise() override;
        
        void Update(float dt);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        float antennaAnimationTimer = 0.0f;
        float nextAntennaAnimation = 3.0f;
        float topOfHeadOffset = 46.0f;
};
