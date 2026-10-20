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
    bool IsWaveComplete() const;
    void AdvanceSleep(float dt);
};