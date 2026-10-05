#pragma once

#include "BodyDimensions.h"
#include "RobotState.h"
#include "Eye.h"

class Eyes
{
    public:
        Eyes(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise();
        void ShutDown();

        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        void Blink(float dt);
        void CloseLeft(float dt);
        void CloseRight(float dt);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;

        Eye leftEye;
        Eye rightEye;

        float blinkTimer = 0.0f;
        float nextBlink = 0.0f;
        bool wasLeftEyeClosed = false;
        bool wasRightEyeClosed = false;
}; 
