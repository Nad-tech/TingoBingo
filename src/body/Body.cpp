#include "Body/Body.h"
#include <cmath>

Body::Body(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    bodyBase(dimensions),
    neck(dimensions, robotState),
    pelvis(dimensions, robotState),
    arms(dimensions, robotState)
{}

void Body::Initialise()
{
    bodyBase.Initialise();
    neck.Initialise();
    arms.Initialise();
    pelvis.Initialise();
}

void Body::Shutdown()
{
    neck.Shutdown();
    arms.Shutdown();
    pelvis.Shutdown();
}

void Body::Update(float dt)
{
    neck.Update(dt);
    arms.Update(dt);
    pelvis.Update(dt);
}

void Body::Draw() const
{
    bodyBase.Draw();
    arms.Draw();
    neck.Draw();
    pelvis.Draw();
}

void Body::SetTransform(MyTransform transform)
{
    this->transform = transform;

    bodyBase.SetTransform(this->transform);
    neck.SetTransform(this->transform);
    arms.SetTransform(this->transform);
    pelvis.SetTransform(this->transform);
}