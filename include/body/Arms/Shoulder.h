#pragma once 

#include "Shape.h"
#include "UpperArm.h"
#include "BodyDimensions.h"
#include "Emotion.h"

class Shoulder : public Shape
{
    public:
        Shoulder(BodyDimensions& dimensions, std::string side);

        void Initialise() override;

        void Update(float dt, Emotion emotion);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void SwingArm(float dt, float swingMinAngle, float swingMaxAngle);

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset = {0, 0};

        std::string side = "";
        UpperArm upperArm;

        std::string name;
};