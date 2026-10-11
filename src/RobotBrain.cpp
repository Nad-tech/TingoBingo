#include "RobotBrain.h"
#include "Robot.h"

RobotBrain::RobotBrain(Robot& robot, RobotState& robotState) : 
    robot(robot),
    robotState(robotState),
    speechController()
{}

void RobotBrain::Initialise()
{
   
}

void RobotBrain::Update(float dt)
{
    Vector2 p = {0,0};
    robot.LookAt(p);

    float idleTimeOut = 5.0f;
    idleTimer += dt;

    //Idle behavior
    if 
    (
        robotState.brainState == RobotState::BrainState::Idle && 
        idleTimer >= idleTimeOut && 
        !robotState.speaking
    )
    {
        SpeakRandomIdlePhrase();
        
        std::uniform_int_distribution<> dist
        (
            0, robotState.gestures.idleGestureNames.size() - 1
        );
        int idx = dist(gen);
        lastIdleMovement = robotState.gestures.idleGestureNames[idx];
        
        ChooseIdleMovement(true);
        idleTimer = 0.0f;
    }
    
    speechController.Update();

    if(speechController.SpeechFinished())
    {
        robotState.speaking = false;
        ChooseIdleMovement(false);
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

void RobotBrain::SpeakRandomIdlePhrase()
{
 
    std::uniform_int_distribution<> dist(0, phrases.idlePhrases.size() - 1);

    int idx = dist(gen);

    Speak(phrases.idlePhrases[idx]);
}

void RobotBrain::ChooseIdleMovement(bool enable)
{            
    if(enable)
    {
        if(lastIdleMovement == "nod") robotState.gestures.nod = true;
        if(lastIdleMovement == "shakeHead") robotState.gestures.shakeHead = true;
        if(lastIdleMovement == "waveLeft") robotState.gestures.waveLeft = true;
        if(lastIdleMovement == "waveRight") robotState.gestures.waveRight = true;
        if(lastIdleMovement == "shrug") robotState.gestures.shrug = true;
        if(lastIdleMovement == "crouch") robotState.gestures.crouch = true;
        if(lastIdleMovement == "closeLeftEye") robotState.gestures.closeLeftEye = true;
        if(lastIdleMovement == "closeRightEye") robotState.gestures.closeRightEye = true;
        if(lastIdleMovement == "closeRightClamp") robotState.gestures.closeRightClamp = true;
        if(lastIdleMovement == "closeLeftClamp") robotState.gestures.closeLeftClamp = true;
    }
    else
    {
        if(lastIdleMovement == "nod") robotState.gestures.nod = false;
        if(lastIdleMovement == "shakeHead") robotState.gestures.shakeHead = false;
        if(lastIdleMovement == "waveLeft") robotState.gestures.waveLeft = false;
        if(lastIdleMovement == "waveRight") robotState.gestures.waveRight = false;
        if(lastIdleMovement == "shrug") robotState.gestures.shrug = false;
        if(lastIdleMovement == "crouch") robotState.gestures.crouch = false;
        if(lastIdleMovement == "closeLeftEye") robotState.gestures.closeLeftEye = false;
        if(lastIdleMovement == "closeRightEye") robotState.gestures.closeRightEye = false;
        if(lastIdleMovement == "closeRightClamp") robotState.gestures.closeRightClamp = false;
        if(lastIdleMovement == "closeLeftClamp") robotState.gestures.closeLeftClamp = false;
    }
}