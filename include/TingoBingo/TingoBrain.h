#pragma once
#include "TingoBingo/TingoState.h"
#include "SpeechController.h"
#include <string>


class Tingo;
class TingoBrain
{
public:
    enum class WaveSequence
    {
        Waiting,
        RightArm,
        WaitingForRightArm,
        WaitingBetweenArms,
        LeftArm,
        WaitingForLeftArm
    };

    enum class BlinkSequence
    {
        Blinking,
        WaitingBetweenBlinks
    };

    enum class SleepSequence
    {
        Inactive,
        PreparingToSleep,
        WaitingForLimbs,
        ClosingEyes,
        Sleeping,
        WakingUp,
        Finished
    };

    TingoBrain(Tingo& tingo, TingoState& state);
    void Initialise();

    void Update(float dt);
    void Draw();
    
private:
    Tingo& tingo;
    TingoState& state;

    float idleWaveTimer;
    float waveDurationTimer;
    float idleTimer;

    WaveSequence waveSequence;
    void AdvanceIdleWave(float dt);
    
    BlinkSequence blinkSequence;
    void AdvanceBlink(float dt);

    float blinkTimer;
    float nextBlinkTimer;

    SleepSequence sleepSequence;
    void AdvanceSleep(float dt);
    float sleepTimer;

    void AdvanceGreeting(float dt);

    SpeechController speechController;
    void Speak(std::string text);
};