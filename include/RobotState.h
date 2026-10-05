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
            bool kickLeft = false;
            bool kickRight = false;
            bool jump = false;
            bool shrug = false;
            bool celebrate = false;
            bool crouch = false;
            bool spin = false;
            bool closeLeftEye = false;
            bool closeRightEye = false;
        };
        Gestures gestures;

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
