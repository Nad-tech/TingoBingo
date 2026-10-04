#pragma once

#include "Shoulder.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
#include "RobotState.h"

class Arms
{
    public:
        Arms(BodyDimensions& dimensions, RobotState& robotState);

        void Initialise();
        void Shutdown();

        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void Wave();
        void Shrug();
        
    private:
        BodyDimensions& dimensions;
        RobotState& robotState;

        Shoulder leftShoulder;
        Shoulder rightShoulder;
};