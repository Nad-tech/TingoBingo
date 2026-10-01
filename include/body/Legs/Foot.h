#pragma once

#include "BodyDimensions.h"
#include "Shape.h"
#include <string>
#include "Emotion.h"

class Foot : public Shape
{
    public:
        Foot(BodyDimensions& dimensions, std::string side);
        
        void Initialise() override;
        void Update(float dt, Emotion emotion);
        
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        std::string side;
};