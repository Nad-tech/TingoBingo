#include "TingoBingo/TingoBrain.h"
#include "TingoBingo/Tingo.h"

TingoBrain::TingoBrain(Tingo& tingo, TingoState& state) :
    tingo(tingo),
    state(state)
{}

void TingoBrain::Initialise()
{
    state.brainState = TingoState::BrainState::Idle;
    state.waveState = TingoState::WaveState::Inactive;
    
    waveSequence = WaveSequence::Waiting;
    
    idleWaveTimer = 0.0f;
    idleTimer = 0.0f;
    sleepTimer = 0.0f;
    waveDurationTimer = 0.0f;
}

void TingoBrain::Update(float dt)
{
    switch (state.brainState)
    {
    case TingoState::BrainState::Idle:
        AdvanceIdleWave(dt);
        idleTimer += dt;
        if(idleTimer > 60)
        {
            state.brainState = TingoState::BrainState::Sleeping;
            state.waveState = TingoState::WaveState::Inactive;
            state.blinkState = TingoState::BlinkState::Disable;
            idleTimer = 0.0f;
            idleWaveTimer = 0.0f;
        }
        break;
    
    case TingoState::BrainState::Sleeping:
        AdvanceSleep(dt);
        sleepTimer += dt;
        if(sleepTimer > 10)
        {
            state.brainState = TingoState::BrainState::Idle;
            state.blinkState = TingoState::BlinkState::Enable;
            sleepTimer = 0.0f;
        }
        break;
    
    default:
        break;
    }    
}

void TingoBrain::Draw()
{

}

void TingoBrain::AdvanceIdleWave(float dt)
{
    switch (waveSequence)
    {
        case WaveSequence::Waiting:
        {
            state.waveState = TingoState::WaveState::Inactive;
            idleWaveTimer += dt;

            if (idleWaveTimer >= 5.0f)
            {
                state.waveState = TingoState::WaveState::WaveRight;
                waveDurationTimer = 0.0f;
                idleWaveTimer = 0.0f;
                waveSequence = WaveSequence::RightArm;
            }
            break;
        }

        case WaveSequence::RightArm:
        {
            if (tingo.GetRightArmWaveState() == ArmWaveState::Waving)
            {
                waveDurationTimer += dt;

                if (waveDurationTimer >= 2.0f)
                {
                    state.waveState = TingoState::WaveState::Inactive;
                    waveSequence = WaveSequence::WaitingForRightArm;
                }
            }
            break;
        }

        case WaveSequence::WaitingForRightArm:
        {
            if (tingo.GetRightArmWaveState() == ArmWaveState::None)
            {
                idleWaveTimer = 0.0f;
                waveSequence = WaveSequence::WaitingBetweenArms;
            }
            break;
        }

        case WaveSequence::WaitingBetweenArms:
        {
            idleWaveTimer += dt;

            if (idleWaveTimer >= 2.0f)
            {
                state.waveState = TingoState::WaveState::WaveLeft;
                waveDurationTimer = 0.0f;
                idleWaveTimer = 0.0f;
                waveSequence = WaveSequence::LeftArm;
            }
            break;
        }

        case WaveSequence::LeftArm:
        {
            if (tingo.GetLeftArmWaveState() == ArmWaveState::Waving)
            {
                waveDurationTimer += dt;

                if (waveDurationTimer >= 2.0f)
                {
                    state.waveState = TingoState::WaveState::Inactive;
                    waveSequence = WaveSequence::WaitingForLeftArm;
                }
            }
            break;
        }

        case WaveSequence::WaitingForLeftArm:
        {
            if (tingo.GetLeftArmWaveState() == ArmWaveState::None)
            {
                idleWaveTimer = 0.0f;
                waveDurationTimer = 0.0f;
                waveSequence = WaveSequence::Waiting;
            }
            break;
        }
    }
}

void TingoBrain::AdvanceSleep(float dt)
{
    (void)dt;
    switch (state.blinkState)
    {
    case TingoState::BlinkState::Disable:
        /* code */
        break;
    
    
    default:
        break;
    }
}

bool TingoBrain::IsWaveComplete() const
{
    switch (state.waveState)
    {
        case TingoState::WaveState::WaveRight:
            return tingo.GetRightArmWaveState() == ArmWaveState::None;

        case TingoState::WaveState::WaveLeft:
            return tingo.GetLeftArmWaveState() == ArmWaveState::None;

        case TingoState::WaveState::Inactive:
            return true;

        default:
            return false;
    }
}