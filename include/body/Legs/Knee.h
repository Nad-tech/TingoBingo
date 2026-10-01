#pragma once

#include "BodyDimensions.h"
#include "Shape.h"
#include "Shin.h"
#include <string>
#include "Emotion.h"

class Knee : public Shape
{
    public:
        Knee(BodyDimensions& dimensions, std::string side);
        
        void Initialise() override;
        
        void Update(float dt, Emotion emotion);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        std::string side;

        Shin shin;
};