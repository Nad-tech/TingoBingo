#pragma once
#include "TingoBingo/TingoState.h"

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

    float sleepTimer;
    float sleepingTimer;

    WaveSequence waveSequence;
    void AdvanceIdleWave(float dt);
    void AdvanceSleep(float dt);
    
    BlinkSequence blinkSequence;
    void AdvanceBlink(float dt);

    float blinkTimer;
    float nextBlinkTimer;
};