#pragma once

#include "Shape.h"
#include "Knee.h"
#include "BodyDimensions.h"
#include "MyTransform.h"

#include <string>

class Thigh : public Shape
{
    public:
        Thigh(BodyDimensions& dimensions, std::string side);
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        std::string side;
        Knee knee;
};