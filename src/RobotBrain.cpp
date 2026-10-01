
#include "RobotBrain.h"
#include "Robot.h"
#include "Emotion.h"
#include "BodyDimensions.h"
#include "raylib.h"


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

const char* RobotBrain::RobotStateToString(State state)
{
    switch (state)
    {
        case State::Idle:      return "Idle";
        case State::Speaking:  return "Speaking";
        case State::Thinking:  return "Thinking";
        case State::Listening: return "Listening";
        case State::Reacting:  return "Reacting";
        default:               return "Unknown";
    }
}

const char* RobotBrain::EmotionToString(Emotion emotion)
{
    switch (emotion)
    {
        case Emotion::Neutral:   return "Neutral";
        case Emotion::Happy:     return "Happy";
        case Emotion::Sad:       return "Sad";
        case Emotion::Angry:     return "Angry";
        case Emotion::Surprised: return "Surprised";
        default:                 return "Unknown";
    }
}

void RobotBrain::NextEmotion()
{
    int next = static_cast<int>(emotion) + 1;

    if (next >= static_cast<int>(Emotion::Count))
    {
        next = 0;
    }

    emotion = static_cast<Emotion>(next);
}

void RobotBrain::NextState()
{
    int next = static_cast<int>(state) + 1;

    if (next >= static_cast<int>(State::Count))
    {
        next = 0;
    }

    state = static_cast<State>(next);
}

void RobotBrain::Draw() const
{
    DrawText(
        TextFormat("RobotBrain State: %s", RobotStateToString(state)),
        10, 10, 20, WHITE
    );

    DrawText(
        TextFormat("RobotBrain Emotion: %s", EmotionToString(emotion)),
        10, 30, 20, WHITE
    );
}