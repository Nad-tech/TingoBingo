#pragma once

#include "RobotState.h"
#include "SpeechController.h"
#include "Phrases.h"

#include <string>
#include <vector>
#include <random>
#include <raylib.h>

class Robot;

class RobotBrain
{
    public:
        RobotBrain(Robot& robot, RobotState& robotState);

        void Initialise();

        void Update(float dt);
        void Draw() const;

        void Speak(std::string text);

        void Search();

    private:
        void AdvanceSearch(float dt);
        void AdvanceIdleGaze(float dt);

        void SpeakRandomIdlePhrase();
        void ChooseIdleMovement(bool enable);

        Robot& robot;
        RobotState& robotState;

        SpeechController speechController;

        Phrases phrases;

        std::mt19937 gen{ std::random_device{}() };

        // Idle behaviour.
        float idleTimer = 0.0f;
        float idleLookTimer = 0.0f;

        std::string lastIdleMovement;

        // Environmental search.
        float searchLookTimer = 0.0f;

        Vector2 searchCentre = { 0.0f, 0.0f };

        float searchHorizontalAngle = 0.0f;
        float searchHorizontalDirection = 1.0f;
        float searchVerticalAngle = 0.0f;

        // Current gaze target.
        Vector2 lookTarget = { 0.0f, 0.0f };

        // Search ray debug drawing.
        float eyeOffset = 40.0f;
        Vector2 searchRayOrigin = { 0.0f, 0.0f };
        Vector2 searchRayEnd = { 0.0f, 0.0f };
};