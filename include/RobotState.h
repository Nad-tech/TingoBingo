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
            bool celebrate = false;
        };
        Gestures gestures;

        enum class Gesture
        {
            Idle,
            Nod,
            ShakeHead,
            WaveLeft,
            WaveRight,
            Shrug,
            Celebrate
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

        enum class Emotions
        {
            Idle,
            Happy,
            Sad,
            Angry,
            Surprised
        };
        Emotions emotion = Emotions::Idle;
};
