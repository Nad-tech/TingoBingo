#pragma once

#include "body/Legs/Thigh.h"
#include "BodyDimensions.h"
#include "Shape.h"
#include "MyTransform.h"

class Legs : Shape
{
    public:
        Legs(BodyDimensions& dimensions);
        void Initialise();
        void Shutdown();
        
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        Thigh rightThigh;
        Thigh leftThigh;
};