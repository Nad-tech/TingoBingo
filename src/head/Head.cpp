//====================================================
// Head.cpp
//
// Coordinates all of the robot's head components.
//
// The Head class owns the individual facial features
// (head base, eyes, mouth, ears, antenna, nose,
// eyebrows and pupils) and keeps them synchronised by
// updating, drawing, positioning and rotating them as
// a single unit.
//
// It also controls the head's idle animations,
// including bobbing and wiggling.
//====================================================

#include "Body/Head/Head.h"
#include <cmath>

// Initialise the head's transform and idle animation state.
Head::Head(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    headBase(dimensions, robotState),
    eyes(dimensions, robotState),
    antenna(dimensions, robotState),
    ears(dimensions, robotState),
    eyebrows(dimensions, robotState),
    mouth(dimensions, robotState),
    nose(dimensions, robotState)
{
}

// Initialise every component that makes up the robot's head.
void Head::Initialise()
{
    headBase.Initialise();
    
    positionOffset = {
        0,
        dimensions.neckHeight / 2.0f + dimensions.headHeight / 2.0f  
    };
    
    antenna.Initialise();
    ears.Initialise();
    eyebrows.Initialise();
    eyes.Initialise();
    mouth.Initialise();
    nose.Initialise();
}

// Release resources used by each head component.
void Head::Shutdown()
{
    headBase.Shutdown();
    eyes.Shutdown();
    mouth.Shutdown();
    ears.Shutdown();
    antenna.Shutdown();
    eyebrows.Shutdown();
    nose.Shutdown();
}

// Update every animated head component.
void Head::Update(float dt)
{
    antenna.Update(dt);
    ears.Update(dt);
    eyebrows.Update(dt);
    eyes.Update(dt);
    mouth.UpdateMouth(dt);
    nose.Update(dt);
}

void Head::Draw() const
{
    ears.Draw();
    headBase.Draw();
    eyes.Draw();
    mouth.Draw();
    nose.Draw();
    eyebrows.Draw();
    antenna.Draw();
}

void Head::SetTransform(MyTransform parentTransform)
{
    transform = MakeChildTransform(parentTransform, positionOffset);

    headBase.SetTransform(transform);
    eyes.SetTransform(transform);
    antenna.SetTransform(transform);
    ears.SetTransform(transform);
    eyebrows.SetTransform(transform);
    nose.SetTransform(transform);
    mouth.SetTransform(transform);
}

void Head::LookAt(Vector2 point)
{
    eyes.GetPupils().LookAt(point);
}

void Head::LookForward()
{
    eyes.GetPupils().LookForward();
}