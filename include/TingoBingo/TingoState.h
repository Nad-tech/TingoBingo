#pragma once

class TingoState
{
public:
    bool speaking = false;

    struct Gestures
    {
        bool waveRight = false;
        bool waveLeft = false;
    };
    Gestures gestures;
};