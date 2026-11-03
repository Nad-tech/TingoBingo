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

    enum class WalkState
    {
        Stopped,
        Walking,
        Running
    }walkState = WalkState::Stopped;

    float walkSpeedScale = 0.0f;

    bool speaking;
};