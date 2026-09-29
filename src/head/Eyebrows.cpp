//====================================================
// Eyebrows.cpp
//
// Handles the robot's eyebrow sprites and animation.
// The eyebrows can play idle and emotional animations.
//====================================================

#include "Body/Head/Eyebrows.h"
#include "Constants.h"
#include "Emotion.h"

Eyebrows::Eyebrows(BodyDimensions& dimensions) : dimensions(dimensions)
{}

void Eyebrows::Initialise()
{
    dimensions.eyeBrowsWidth = 100;
    dimensions.eyeBrowsHeight = 100;

    positionOffset = {
        0,
        foreheadOffset
    };
}

void Eyebrows::Update(float dt, bool speaking, Emotion emotion)
{
    // Speaking and happiness both use the expressive eyebrow animation.
    bool happy = speaking || emotion == Emotion::Happy;

    // Start the happy animation immediately when entering the happy state.
    if (happy && !wasHappy)
    {
        // Reset the timer and choose a random delay before the next wiggle.
        happyAnimationTimer = 0.0f;
        nextHappyAnimation = GetRandomValue(1000, 5000) / 1000.0f;

        wasHappy = true;
        return;
    }

    // While happy, occasionally repeat the eyebrow wiggle.
    if (happy)
    {
        happyAnimationTimer += dt;

        if (happyAnimationTimer > nextHappyAnimation)
        {
    
            // Reset the timer and choose a new random interval.
            happyAnimationTimer = 0.0f;
            nextHappyAnimation =
                GetRandomValue(1000, 5000) / 1000.0f;
        }

        return;
    }

    // Restore the idle animation when the happy state ends.
    if (wasHappy)
    {
    
        // Reset the idle timer so the next idle animation is delayed.
        idleAnimationTimer = 0.0f;
        nextIdleAnimation =
            GetRandomValue(1000, 5000) / 1000.0f;

        wasHappy = false;
        return;
    }

    // In the neutral state, occasionally play a small idle movement.
    idleAnimationTimer += dt;

    if (idleAnimationTimer > nextIdleAnimation)
    {
    
        // Reset the timer and randomise the next idle movement.
        idleAnimationTimer = 0.0f;
        nextIdleAnimation =
            GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Eyebrows::SetTransform(MyTransform parentTransform) 
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
}
