#include "RobotBrain.h"
#include "Robot.h"

RobotBrain::RobotBrain(Robot& robot, RobotState& robotState) : 
    robot(robot),
    robotState(robotState),
    speechController()
{}

int rrrrrr = 0;
void RobotBrain::Update(float dt)
{
    rrrrrr += dt;

    speechController.Update();

    if(speechController.SpeechFinished())
    {
        robotState.speaking = false;
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




