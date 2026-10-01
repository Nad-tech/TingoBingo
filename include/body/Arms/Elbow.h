#pragma once

#include "Shape.h"
#include "ForeArm.h"
#include "BodyDimensions.h"
#include "Emotion.h"

#include <string>

class Elbow : public Shape
{
    public:
        Elbow(BodyDimensions& dimensions, std::string side);
        
        void Initialise() override;
        
        void Update(float dt, Emotion emotion);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        std::string side = "";

        ForeArm foreArm;
};