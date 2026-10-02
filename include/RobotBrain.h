#pragma once

#include "RobotState.h"

class Robot;

class RobotBrain
{
    public:

        RobotBrain(Robot& robot, RobotState& robotState);

        void Update(float dt);
        void Draw() const;
        
    private:
        Robot& robot;
        RobotState& robotState;
};