#include "Robot.h"
#include "RobotBrain.h"
#include "Emotion.h"

Robot::Robot() :
    body(dimensions),
    robotBrain(*this)
{}

void Robot::Initialise()
{
    body.Initialise();
}

void Robot::Update(float dt)
{
    body.Update(dt, robotBrain.GetEmotion());

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

void Robot::SetEmotion(Emotion emotion)
{
    robotBrain.SetEmotion(emotion);
}

Emotion Robot::GetEmotion()
{
    return robotBrain.GetEmotion();
}