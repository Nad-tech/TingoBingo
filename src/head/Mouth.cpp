//====================================================
// Mouth.cpp
//
// Handles the robot's mouth sprite and idle animation.
// The mouth can play a simple animation to give the
// robot a more lifelike appearance.
//====================================================

#include "Body/Head/Mouth.h"
#include "Constants.h"
#include "Emotion.h"

Mouth::Mouth(BodyDimensions& dimensions) : dimensions(dimensions)
{}

// Load the mouth sprite sheet and initialise its animation.
void Mouth::Initialise()
{
    dimensions.mouthWidth = 100;
    dimensions.mouthHeight = 100;

    positionOffset = {
        0,
        0
    };
}

// Advance the mouth animation.
void Mouth::UpdateMouth(float dt, bool speaking, Emotion emotion)
{
    
    if (emotion == Emotion::Happy && !speaking)
    {
        frame = 0;
        frameTimer = 0.0f;
        return;
    }

    if (!speaking)
    {
        frame = 1;
        frameTimer = 0.0f;
        return;
    }

    //Animate mouth while speaking
    frameTimer += dt;

    if (frameTimer >= FRAME_DURATION)
    {
        frameTimer -= FRAME_DURATION;
        frame = (frame == 1) ? 2 : 1;
    }
}

void Mouth::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
}
