#pragma once

class TingoState
{
public:    
    enum class BrainState
    {
        Idle,
        Sleeping
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
};