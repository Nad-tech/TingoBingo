#pragma once
#include <vector>
#include <string>

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
            bool closeRightClamp = false;
            bool closeLeftClamp = false;
            bool listening = false;

            std::vector<std::string> gestureNames = {
                "idle",
                "nod",
                "shakeHead",
                "waveLeft",
                "waveRight",
                "kickLeft",
                "kickRight",
                "jump",
                "shrug",
                "celebrate",
                "crouch",
                "spin",
                "closeLeftEye",
                "closeRightEye",
                "closeRightClamp",
                "closeLeftClamp",
                "listening"
            };

            std::vector<std::string> idleGestureNames = {
                "nod",
                "shakeHead",
                "waveLeft",
                "waveRight",
                "shrug",
                "crouch",
                "closeLeftEye",
                "closeRightEye",
                "closeRightClamp",
                "closeLeftClamp"
            };
        };
        Gestures gestures;
    
        enum class BrainState
        {
            Idle,
            Thinking,
            Listening,
            Searching,
            Reacting
        };
        BrainState brainState = BrainState::Idle;
        
        bool speaking = false;

        enum class Emotions
        {
            None,
            Happy,
            Sad,
            Angry,
            Surprised
        };
        Emotions emotion = Emotions::None;
};
