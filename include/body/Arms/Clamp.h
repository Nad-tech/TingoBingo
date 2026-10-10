#pragma once

#include "Finger.h"
#include "RobotState.h"

class Clamp
{
    public:
        Clamp(BodyDimensions& dimensions, RobotState& robotState);

        void Initialise();
        void Shutdown();

        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);
        
        void CloseClamp();
        void OpenClamp();

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;

        Finger leftFinger;
        Finger rightFinger; 
};