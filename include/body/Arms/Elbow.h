#pragma once

#include "Shape.h"
#include "ForeArm.h"
#include "BodyDimensions.h"

#include <string>

class Elbow : public Shape
{
    public:
        Elbow(BodyDimensions& dimensions, std::string side);
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        float localRotation = 0.0f;
        float homeRotation = 0.0f;

        std::string side = "";

        ForeArm foreArm;
};