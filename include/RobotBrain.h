#pragma once

#include "Emotion.h"

class Robot;

class RobotBrain
{
    public:
        enum class State
        {
            Idle,
            Searching,
            Reacting
        };

        RobotBrain(Robot& robot);

        void Update(float dt);

        void SetState(State newState);
        
        void SetEmotion(Emotion newEmotion);
        Emotion GetEmotion();
        
    private:
        Robot& robot;
        State state;
        Emotion emotion;
};