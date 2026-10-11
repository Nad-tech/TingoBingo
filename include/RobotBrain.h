#pragma once

#include "RobotState.h"
#include "SpeechController.h"

class Robot;

class RobotBrain
{
    public:

        RobotBrain(Robot& robot, RobotState& robotState);

        void Update(float dt);
        void Draw() const;

        void Speak(std::string text);
        
    private:
        Robot& robot;
        RobotState& robotState;

        SpeechController speechController;
};