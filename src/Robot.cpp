#include "Robot.h"
#include "RobotBrain.h"

Robot::Robot() :
    body(dimensions, robotState),
    robotBrain(*this, robotState)
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

    const char* stateName = "Unknown";
    switch (robotState.state)
    {
        case RobotState::State::Idle: stateName = "Idle"; break;
        case RobotState::State::Thinking: stateName = "Thinking"; break;
        case RobotState::State::Listening: stateName = "Listening"; break;
        case RobotState::State::Reacting: stateName = "Reacting"; break;
    }

    const char* emotionName = "Unknown";
    switch (robotState.emotion)
    {
        case RobotState::Emotions::Neutral: emotionName = "Neutral"; break;
        case RobotState::Emotions::Happy: emotionName = "Happy"; break;
        case RobotState::Emotions::Sad: emotionName = "Sad"; break;
        case RobotState::Emotions::Angry: emotionName = "Angry"; break;
        case RobotState::Emotions::Surprised: emotionName = "Surprised"; break;
    }

    const auto flag = [](bool value) { return value ? "ON" : "off"; };
    const auto& gestures = robotState.gestures;
    const int x = 12;
    int y = 12;
    const int lineHeight = 18;
    DrawText("ROBOT STATE", x, y, 16, YELLOW); y += lineHeight;
    DrawText(TextFormat("State: %s", stateName), x, y, 14, RAYWHITE); y += lineHeight;
    DrawText(TextFormat("Emotion: %s  Speaking: %s", emotionName, flag(robotState.speaking)), x, y, 14, RAYWHITE); y += lineHeight;
    DrawText(TextFormat("Gestures: idle %s | nod %s | shake %s", flag(gestures.idle), flag(gestures.nod), flag(gestures.shakeHead)), x, y, 14, RAYWHITE); y += lineHeight;
    DrawText(TextFormat("           waveL %s | waveR %s | shrug %s", flag(gestures.waveLeft), flag(gestures.waveRight), flag(gestures.shrug)), x, y, 14, RAYWHITE); y += lineHeight;
    DrawText(TextFormat("           point %s | celebrate %s", flag(gestures.point), flag(gestures.celebrate)), x, y, 14, RAYWHITE);
}

void Robot::CycleState()
{
    switch (robotState.state)
    {
        case RobotState::State::Idle: robotState.state = RobotState::State::Thinking; break;
        case RobotState::State::Thinking: robotState.state = RobotState::State::Listening; break;
        case RobotState::State::Listening: robotState.state = RobotState::State::Reacting; break;
        case RobotState::State::Reacting: robotState.state = RobotState::State::Idle; break;
    }
}

void Robot::CycleEmotion()
{
    switch (robotState.emotion)
    {
        case RobotState::Emotions::Neutral: robotState.emotion = RobotState::Emotions::Happy; break;
        case RobotState::Emotions::Happy: robotState.emotion = RobotState::Emotions::Sad; break;
        case RobotState::Emotions::Sad: robotState.emotion = RobotState::Emotions::Angry; break;
        case RobotState::Emotions::Angry: robotState.emotion = RobotState::Emotions::Surprised; break;
        case RobotState::Emotions::Surprised: robotState.emotion = RobotState::Emotions::Neutral; break;
    }
}

void Robot::ToggleSpeaking()
{
    robotState.speaking = !robotState.speaking;
}

void Robot::ToggleGesture(RobotState::Gesture gesture)
{
    switch (gesture)
    {
        case RobotState::Gesture::Idle: robotState.gestures.idle = !robotState.gestures.idle; break;
        case RobotState::Gesture::Nod: robotState.gestures.nod = !robotState.gestures.nod; break;
        case RobotState::Gesture::ShakeHead: robotState.gestures.shakeHead = !robotState.gestures.shakeHead; break;
        case RobotState::Gesture::WaveLeft: robotState.gestures.waveLeft = !robotState.gestures.waveLeft; break;
        case RobotState::Gesture::WaveRight: robotState.gestures.waveRight = !robotState.gestures.waveRight; break;
        case RobotState::Gesture::Shrug: robotState.gestures.shrug = !robotState.gestures.shrug; break;
        case RobotState::Gesture::Point: robotState.gestures.point = !robotState.gestures.point; break;
        case RobotState::Gesture::Celebrate: robotState.gestures.celebrate = !robotState.gestures.celebrate; break;
    }
}

void Robot::Shutdown()
{
    body.Shutdown();
}
