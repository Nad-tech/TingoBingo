#pragma once

class RobotState
{
    public:
        struct Gestures
        {
            bool idle = false;
            bool nod = false;
            bool shakeHead = false;
            bool waveLeft = false;
            bool waveRight = false;
            bool shrug = false;
            bool point = false;
            bool celebrate = false;
        };

        enum class State
        {
            Idle,
            Thinking,
            Listening,
            Reacting
        };
        State state = State::Idle;
        bool speaking = false;

        enum class Emotion
        {
            Neutral,
            Happy,
            Sad,
            Angry,
            Surprised
        };
};
