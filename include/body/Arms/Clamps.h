#pragma once

#include "Finger.h"
#include "RobotState.h"

class Clamps
{
    public:
        Clamps(BodyDimensions& dimensions, RobotState& robotState);

        void Initialise();
        void Shutdown();

        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        RobotState& robotState;

        Finger upperFinger;
        Finger lowerFinger; 
};