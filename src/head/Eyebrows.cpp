//====================================================
// Eyebrows.cpp
//
// Handles the robot's eyebrow sprites and animation.
// The eyebrows can play idle and emotional animations.
//====================================================

#include "Body/Head/Eyebrows.h"
#include "Constants.h"
#include "Emotion.h"

Eyebrows::Eyebrows(BodyDimensions& dimensions) : 
    dimensions(dimensions)
{}

void Eyebrows::Initialise()
{
    texture = LoadTexture("assets/images/TingoBingo/head/eyebrows.png");

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.3f;

    dimensions.eyeBrowsWidth = texture.width / COLUMNS;
    dimensions.eyeBrowsHeight = texture.height / ROWS;

    drawGeometry.width = dimensions.eyeBrowsWidth;
    drawGeometry.height = dimensions.eyeBrowsHeight;

    animation.Initialise
    (
        dimensions.eyeBrowsWidth,
        dimensions.eyeBrowsHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0,
        foreheadOffset
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}

void Eyebrows::Update(float dt, bool speaking, Emotion emotion)
{
    Sprite::Update(dt);

    // Speaking and happiness both use the expressive eyebrow animation.
    bool happy = speaking || emotion == Emotion::Happy;

    // Start the happy animation immediately when entering the happy state.
    if (happy && !wasHappy)
    {
        animation.Play(2, 3, AnimationPriority::Emotion);

        // Reset the timer and choose a random delay before the next wiggle.
        happyAnimationTimer = 0.0f;
        nextHappyAnimation = GetRandomValue(1000, 5000) / 1000.0f;

        wasHappy = true;
        return;
    }

    // While happy, occasionally repeat the eyebrow wiggle.
    if (happy)
    {
        animation.Play(2, 3, AnimationPriority::Emotion);

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
        animation.Stop();
        animation.Play(0, 1, AnimationPriority::Idle);

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
        animation.Stop();
        animation.Play(0, 1, AnimationPriority::Idle);

        // Reset the timer and randomise the next idle movement.
        idleAnimationTimer = 0.0f;
        nextIdleAnimation =
            GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Eyebrows::SetTransform(MyTransform parentTransform) 
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    SetScreenCoords();
}
