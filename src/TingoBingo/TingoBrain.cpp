#include "TingoBingo/TingoBrain.h"
#include "TingoBingo/Tingo.h"

TingoBrain::TingoBrain(Tingo& tingo, TingoState& state) :
    tingo(tingo),
    state(state)
{
}

void TingoBrain::Initialise()
{
    state.brainState = TingoState::BrainState::Idle;
    idleTimer = 0.0f;

    state.waveState = TingoState::WaveState::Inactive;
    waveSequence = WaveSequence::Waiting;
    waveDurationTimer = 0.0f;
    idleWaveTimer = 0.0f;

    state.blinkState = TingoState::BlinkState::Inactive;
    blinkSequence = BlinkSequence::WaitingBetweenBlinks;
    blinkTimer = 0.0f;
    nextBlinkTimer = GetRandomValue(2, 6);

    sleepSequence = SleepSequence::Inactive;
    state.eyeStateBrain = TingoState::EyeStateBrain::Open;
    sleepTimer = 0.0f;
    snoreTimer = 0.0f;
    nextSnoreTimer = GetRandomValue(3, 6);

    state.speaking = false;

    randomPhraseTimer = GetRandomValue(10, 20);

    gazeTimer = 0.0f;
    nextGazeTimer = static_cast<float>(GetRandomValue(1, 3));
}

void TingoBrain::Update(float dt)
{
    speechController.Update();

    randomPhraseTimer -= dt;

    if(randomPhraseTimer <= 0)
    {
        if(!state.speaking)
        {
            Speak(ChooseRandomPhrase());
            randomPhraseTimer = GetRandomValue(10, 20);
        }
    }

    if(speechController.SpeechFinished())
    {
        state.speaking = false;
    }
    else
    {
        state.speaking = true;
    }


    switch (state.brainState)
    {
        case TingoState::BrainState::Idle:
        {
            AdvanceIdleWave(dt);
            AdvanceBlink(dt);
            AdvanceIdleGaze(dt);

            idleTimer += dt;

            if (idleTimer > 30.0f)
            {
                Speak("I am going to sleep");
                state.brainState = TingoState::BrainState::Sleeping;

                idleTimer = 0.0f;
                idleWaveTimer = 0.0f;
            }

            break;
        }

        case TingoState::BrainState::Sleeping:
        {
            AdvanceSleep(dt);
            break;
        }

        case TingoState::BrainState::Greeting:
        {
            AdvanceGreeting(dt);
            break;
        }

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

        default:
            break;
    }
}

void TingoBrain::AdvanceBlink(float dt)
{
    switch (blinkSequence)
    {
        case BlinkSequence::WaitingBetweenBlinks:
        {
            blinkTimer += dt;

            if (blinkTimer > nextBlinkTimer)
            {
                state.blinkState = TingoState::BlinkState::Blinking;
                blinkSequence = BlinkSequence::Blinking;

                blinkTimer = 0.0f;
                nextBlinkTimer = GetRandomValue(2, 6);
            }

            break;
        }

        case BlinkSequence::Blinking:
        {
            if (
                tingo.GetLeftEyeState() == EyeState::Open &&
                tingo.GetRightEyeState() == EyeState::Open
            )
            {
                state.blinkState = TingoState::BlinkState::Inactive;
                blinkSequence = BlinkSequence::WaitingBetweenBlinks;

                blinkTimer = 0.0f;
            }

            break;
        }

        default:
            break;
    }
}

void TingoBrain::AdvanceSleep(float dt)
{
    switch (sleepSequence)
    {
        case SleepSequence::Inactive:
        {
            sleepSequence = SleepSequence::PreparingToSleep;
            break;
        }

        case SleepSequence::PreparingToSleep:
        {
            state.eyeStateBrain = TingoState::EyeStateBrain::Open;

            sleepSequence = SleepSequence::WaitingForLimbs;
            break;
        }

        case SleepSequence::WaitingForLimbs:
        {
            AdvanceIdleWave(dt);
            AdvanceBlink(dt);

            if 
            (
                tingo.GetRightArmWaveState() == ArmWaveState::None &&
                tingo.GetLeftArmWaveState() == ArmWaveState::None
            )
            {
                state.waveState = TingoState::WaveState::Inactive;
                state.blinkState = TingoState::BlinkState::Inactive;
                state.eyeStateBrain = TingoState::EyeStateBrain::Close;
                sleepSequence = SleepSequence::ClosingEyes;
            }

            break;
        }

        case SleepSequence::ClosingEyes:
        {
            if (
                tingo.GetLeftEyeState() == EyeState::Closed &&
                tingo.GetRightEyeState() == EyeState::Closed
            )
            {
                sleepTimer = 0.0f;
                sleepSequence = SleepSequence::Sleeping;
            }

            break;
        }

        case SleepSequence::Sleeping:
        {
            sleepTimer += dt;
            snoreTimer += dt;

            if(snoreTimer >= nextSnoreTimer)
            {
                if(!state.speaking) 
                { 
                    Speak("Snore");
                }

                snoreTimer = 0.0f;
                nextSnoreTimer = GetRandomValue(3, 6);
            }

            if (sleepTimer > 30.0f)
            {
                sleepSequence = SleepSequence::WakingUp;
                sleepTimer = 0.0f;
            }

            break;
        }        

        case SleepSequence::WakingUp:
        {
            state.eyeStateBrain = TingoState::EyeStateBrain::Open;
            
            if 
            (
                tingo.GetLeftEyeState() == EyeState::Open &&
                tingo.GetRightEyeState() == EyeState::Open
            )
            {
                sleepSequence = SleepSequence::Finished;
            }
            
            break;
        }

        case SleepSequence::Finished:
        {
            // Reset the wave sequence.
            state.waveState = TingoState::WaveState::Inactive;
            waveSequence = WaveSequence::Waiting;
            waveDurationTimer = 0.0f;
            idleWaveTimer = 0.0f;

            // Reset the blink sequence.
            state.blinkState = TingoState::BlinkState::Inactive;
            blinkSequence = BlinkSequence::WaitingBetweenBlinks;
            blinkTimer = 0.0f;
            nextBlinkTimer = GetRandomValue(2, 6);

            // Return to idle.
            idleTimer = 0.0f;
            state.brainState = TingoState::BrainState::Idle;
            sleepSequence = SleepSequence::Inactive;

            Speak("I am waking up");

            break;
        }

    default:
        break;
    }
}

void TingoBrain::AdvanceGreeting(float dt)
{
    (void)dt;
}

void TingoBrain::Speak(std::string text)
{
    speechController.Speak(text);
}

std::string TingoBrain::ChooseRandomPhrase()
{
    int size = phrases.idlePhrases.size();
    int index = GetRandomValue(0, size - 1);

    return phrases.idlePhrases[index];
}

void TingoBrain::AdvanceIdleGaze(float dt)
{
    gazeTimer += dt;

    if (gazeTimer < nextGazeTimer)
    {
        return;
    }

    gazeTimer = 0.0f;

    // Choose a new horizontal and vertical gaze target.
    float x = GetRandomValue(-60, 60) / 100.0f;
    float y = GetRandomValue(-60, 60) / 100.0f;

    tingo.SetGazeTarget({x, y});

    // Pause before choosing another direction.
    nextGazeTimer = static_cast<float>(GetRandomValue(2, 5));
}