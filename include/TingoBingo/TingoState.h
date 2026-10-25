#pragma once

class TingoState
{
public:    
    enum class BrainState
    {
        Idle,
        Sleeping,
        Greeting
    } brainState;

    enum class WaveState
    {
        Inactive,
        WaveLeft,
        WaveRight
    } waveState;

    enum class BlinkState
    {
        Inactive,
        Blinking
    } blinkState;

    enum class EyeStateBrain
    {
        Open,
        Close
    }eyeStateBrain;

    bool speaking;
};