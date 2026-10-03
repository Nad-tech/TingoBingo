#pragma once

#include "Body/Legs/Thigh.h"
#include "BodyDimensions.h"
#include "Shape.h"
#include "MyTransform.h"
#include "Thigh.h"
#include "RobotState.h"

class Legs : Shape
{
    public:
        Legs(BodyDimensions& dimensions, RobotState& robotState);
        void Initialise();
        void Shutdown();
        
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        void Crouch();

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Thigh rightThigh;
        Thigh leftThigh;
};