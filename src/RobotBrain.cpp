#include "RobotBrain.h"
#include "Robot.h"

RobotBrain::RobotBrain(Robot& robot, RobotState& robotState) : 
    robot(robot),
    robotState(robotState),
    speechController()
{}

void RobotBrain::Update(float dt)
{
    idleTimer += dt;

    if(idleTimer >= 10.0f)
    {
        Speak(phrases.idleHello);
        idleTimer = 0.0f;
        robotState.gestures.waveRight = true;
    }

    speechController.Update();

    if(speechController.SpeechFinished())
    {
        robotState.speaking = false;
        robotState.gestures.waveRight = false;
    }
    else {
        robotState.speaking = true;
    }
}

void RobotBrain::Draw() const
{

}

void RobotBrain::Speak(std::string text)
{
    speechController.Speak(text);
}




