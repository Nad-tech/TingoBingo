//====================================================
// Eyes.cpp
//
// Handles the robot's eye sprites and blink animation.
// The eyes are animated independently from the head,
// allowing facial expressions without changing the
// head rotation sprite.
//====================================================

#include "Body/Head/Eyes.h"
#include "Constants.h"
#include <cmath>

Eyes::Eyes(BodyDimensions& dimensions) : 
    dimensions(dimensions),
    pupils(dimensions)
{
}

void Eyes::Initialise()
{
    dimensions.eyesWidth = 100;
    dimensions.eyesHeight = 100;

    dimensions.eyesYoffset = 30.0f;

    positionOffset = {
        0, dimensions.eyesYoffset
    };

    pupils.Initialise();
}

void Eyes::Update(float dt)
{
    idleAnimationTimer += dt;
    
    if(idleAnimationTimer > nextIdleAnimation)
    {
        idleAnimationTimer = 0.0f;
        nextIdleAnimation = GetRandomValue(1000, 5000) / 1000.0f;
    }

    pupils.Update(dt);
}

void Eyes::Draw() const
{
    pupils.Draw();
}

void Eyes::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);

    pupils.SetTransform(transform);
}

Pupils& Eyes::GetPupils()
{
    return pupils;
}

void Eyes::LookAt(Vector2 point)
{
    pupils.LookAt(point);
}

void Eyes::LookForward()
{
    pupils.LookForward();
}

void Eyes::Shutdown()
{
    pupils.Shutdown();
}