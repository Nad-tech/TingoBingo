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
    eyes.ShutDown();
    mouth.Shutdown();
    ears.Shutdown();
    antenna.Shutdown();
    eyebrows.ShutDown();
    nose.Shutdown();
}

// Update every animated head component.
void Head::Update(float dt)
{
    Nod();

    if(nodState != NodState::None)
    {
        AdvanceNod(dt);
    }

    Shrug();

    if(shrugState != ShrugState::None)
    {
        AdvanceShrug(dt);
    }

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
    tempParentTransform = parentTransform;

    transform = MakeChildTransform(parentTransform, positionOffset);

    transform.position.y += YOffset;

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
    //eyes.GetPupils().LookAt(point);
}

void Head::LookForward()
{
    //eyes.GetPupils().LookForward();
}

void Head::Nod()
{
    if(robotState.gestures.nod && nodState == NodState::None)
    {
        nodState = NodState::Lowering;
    }
}

void Head::AdvanceNod(float dt)
{
    const float speed = 250.0f;
    const float minOffset = -30.0f;
    const float maxOffset = 5.0f;

    if(nodState == NodState::Raising)
    {
        YOffset += speed * dt;

        if(YOffset >= maxOffset)
        {
            YOffset = maxOffset;
            nodState = NodState::Lowering;
        }
    }
    else if(nodState == NodState::Lowering)
    {
        YOffset -= speed * dt;

        if(YOffset <= minOffset)
        {
            YOffset = minOffset;
        
            if(robotState.gestures.nod)
            {
                nodState = NodState::Raising;
            }
            else
            {
                nodState = NodState::Returning;
            }
        }
    }
    else if(nodState == NodState::Returning)
    {
        if(YOffset > 0.0f)
        {
            YOffset -= speed * dt;

            if(YOffset <= 0.0f)
            {
                YOffset = 0.0f;
                nodState = NodState::None;
            }
        }
        else if(YOffset < 0.0f)
        {
            YOffset += speed * dt;

            if(YOffset >= 0.0f)
            {
                YOffset = 0.0f;
                nodState = NodState::None;
            }
        }
        else
        {
            nodState = NodState::None;
        }
    }

    SetTransform(tempParentTransform);
}

void Head::Shrug()
{
    if(robotState.gestures.shrug && shrugState == ShrugState::None)
    {
        shrugState = ShrugState::Lowering;
    }
}

void Head::AdvanceShrug(float dt)
{
    const float speed = 250.0f;
    const float minOffset = -30.0f;

    if(shrugState == ShrugState::Lowering)
    {
        YOffset -= speed * dt;

        if(YOffset <= minOffset)
        {
            YOffset = minOffset;
        
            if(!robotState.gestures.shrug)
            {
                shrugState = ShrugState::Returning;
            }
        }
    }
    else if(shrugState == ShrugState::Returning)
    {
        if(YOffset < 0.0f)
        {
            YOffset += speed * dt;

            if(YOffset >= 0.0f)
            {
                YOffset = 0.0f;
                shrugState = ShrugState::None;
            }
        }
        else
        {
            nodState = NodState::None;
        }
    }

    SetTransform(tempParentTransform);
}
