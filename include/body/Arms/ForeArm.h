#pragma once

#include "BodyDimensions.h"
#include <string>

#include "Shape.h"
#include "Hand.h"

class ForeArm : public Shape
{
    public:
        ForeArm(BodyDimensions& dimensions, std::string side);
        
        void Initialise();
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        
        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        
        std::string side = "";

        Hand hand;
};