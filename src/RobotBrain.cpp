
#include "RobotBrain.h"
#include "Robot.h"
#include "Emotion.h"
#include "BodyDimensions.h"


RobotBrain::RobotBrain(Robot& robot)
    : robot(robot),
      state(State::Idle),
      emotion(Emotion::Neutral)
{}

inline int rrrr = 0;
void RobotBrain::Update(float dt)
{
    rrrr = dt;
}

void RobotBrain::SetState(State state)
{
    this->state = state;
}

void RobotBrain::SetEmotion(Emotion newEmotion)
{
    emotion = newEmotion;
}

Emotion RobotBrain::GetEmotion()
{
    return emotion;
}