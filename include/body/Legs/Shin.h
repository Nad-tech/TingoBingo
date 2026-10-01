#pragma once
#include "BodyDimensions.h"
#include "Shape.h"
#include "Foot.h"
#include <string>

class Shin : public Shape
{
    public:
        public:
        Shin(BodyDimensions& dimensions, std::string side);
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTrnsform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        std::string side;

        Foot foot;
};