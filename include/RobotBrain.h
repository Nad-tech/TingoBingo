#pragma once

#include "RobotState.h"
#include "SpeechController.h"
#include "Phrases.h"
#include <vector>
#include <random>

class Robot;

class RobotBrain
{
    public:
        RobotBrain(Robot& robot, RobotState& robotState);

        void Initialise();

        void Update(float dt);
        void Draw() const;

        void Speak(std::string text);

        void SpeakRandomIdlePhrase();
        void ChooseIdleMovement(bool enable);
        
    private:
        Robot& robot;
        RobotState& robotState;

        SpeechController speechController;

        Phrases phrases;

        float idleTimer = 0.0f;

        std::mt19937 gen{ std::random_device{}() };

        std::string lastIdleMovement;
};