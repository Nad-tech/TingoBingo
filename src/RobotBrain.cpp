#include "RobotBrain.h"
#include "Robot.h"

RobotBrain::RobotBrain(Robot& robot, RobotState& robotState) : 
    robot(robot),
    robotState(robotState),
    speechController()
{}

inline Vector2 cart2Screen(Vector2 v)
{
    return {
        SCREEN_WIDTH / 2.0f + v.x,
        SCREEN_HEIGHT / 2.0f - v.y
    };
}

void RobotBrain::Initialise()
{

}

void RobotBrain::Update(float dt)
{
    // Update gaze behaviour according to the current brain state.
    if(robotState.brainState == RobotState::BrainState::Idle)
    {
        AdvanceIdleGaze(dt);
    }
    else if(robotState.brainState == RobotState::BrainState::Searching)
    {
        AdvanceSearch(dt);
    }

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
    DrawLine
    (
        cart2Screen(searchRayOrigin).x, 
        cart2Screen(searchRayOrigin).y, 
        cart2Screen(searchRayEnd).x,
        cart2Screen(searchRayEnd).y,
        RED 
    );
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

void RobotBrain::Search()
{
    robotState.brainState = RobotState::BrainState::Searching;
}

void RobotBrain::AdvanceSearch(float dt)
{
    
}

void RobotBrain::AdvanceIdleGaze(float dt)
{
    
}