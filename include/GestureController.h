#pragma once

#include "Body/Body.h"

class GestureController
{
    public:

        enum class Gesture
        {
            None,
            Nod,
            ShakeHead,
            Wave,
            Shrug,
            Point,
            Celebrate
        };

        GestureController(Body& body);

        void Update(float dt);
        void SetGesture(Gesture gesture);

        bool IsPlaying() const;
        Gesture GetGesture() const;

    private:
        Gesture currentGesture;
        Body& body;

        float gestureTimer;
        bool playing;
};