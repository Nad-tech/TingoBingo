#pragma once

#include "Body/Legs/Thigh.h"
#include "BodyDimensions.h"
#include "Shape.h"
#include "MyTransform.h"
#include "Emotion.h"
#include "Thigh.h"

class Legs : Shape
{
    public:
        Legs(BodyDimensions& dimensions);
        void Initialise();
        void Shutdown();
        
        void Update(float dt, Emotion emotion);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Thigh rightThigh;
        Thigh leftThigh;
};