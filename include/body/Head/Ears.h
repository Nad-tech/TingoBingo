#pragma once

#include "BodyDimensions.h"
#include "RobotState.h"
#include "Ear.h"

class Ears
{
    public:
        Ears(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise();
        void ShutDown();

        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;

        Ear leftEar;
        Ear rightEar;
}; 
