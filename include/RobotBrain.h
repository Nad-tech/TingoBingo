#pragma once

#include "Emotion.h"
#include "GestureController.h"

class Robot;

class RobotBrain
{
    public:

        enum class State
        {
            Idle,
            Speaking,
            Thinking,
            Listening,
            Reacting,

            Count
        };
        static const char* RobotStateToString(State state);
        static const char* EmotionToString(Emotion emotion);
        void NextEmotion();
        void NextState();

        RobotBrain(Robot& robot);

        void Update(float dt);

        void SetState(State newState);
        
        void SetEmotion(Emotion newEmotion);
        Emotion GetEmotion();

        void Draw() const;
        
    private:
        Robot& robot;
        State state;
        Emotion emotion;
        GestureController gestureController;
};