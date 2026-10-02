#include "Robot.h"
#include "RobotBrain.h"

Robot::Robot() :
    robotState(robotState),
    body(dimensions, robotState),
    robotBrain(*this)
{}

void Robot::Initialise()
{
    body.Initialise();
}

void Robot::Update(float dt)
{
    body.Update(dt);
    robotBrain.Update(dt);
}

void Robot::SetTransform(MyTransform transform)
{
    this->transform = transform;
    body.SetTransform(this->transform);
}

void Robot::Draw() const
{
    body.Draw();
}

void Robot::Shutdown()
{
    body.Shutdown();
}