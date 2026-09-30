#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"

class Headbase : public Sprite 
{
    public:
        Headbase(BodyDimensions& dimensions);
        void Initialise() override;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        Vector2 globalPivot;

        std::string name = "headBase";
};
