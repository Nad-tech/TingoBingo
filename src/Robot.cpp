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

void Robot::SetTransform(MyTransform initialTransform)
{
    transform = initialTransform;
    body.SetTransform(transform);
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
        case RobotState::Emotions::Idle: emotionName = "Idle"; break;
        case RobotState::Emotions::Happy: emotionName = "Happy"; break;
        case RobotState::Emotions::Sad: emotionName = "Sad"; break;
        case RobotState::Emotions::Angry: emotionName = "Angry"; break;
        case RobotState::Emotions::Surprised: emotionName = "Surprised"; break;
    }

    const auto flag = [](bool value) { return value ? "ON" : "off"; };
    const auto& gestures = robotState.gestures;
    const int x = 12;
    int y = 12;
    const int fontSize = 20;
    const int lineHeight = fontSize + 4;
    
    DrawText("ROBOT STATE", x, y, 16, YELLOW); 
    
    y += lineHeight;
    
    DrawText(
        TextFormat
        (
            "State: %s", stateName
        ), 
        x, 
        y, 
        fontSize, 
        RAYWHITE
    ); 
    
    y += lineHeight;
    
    DrawText(
        TextFormat
        (
            "Emotion: %s  Speaking: %s",
            emotionName, flag(robotState.speaking)
        ), 
        x, 
        y, 
        fontSize, 
        RAYWHITE
    ); 
    
    y += lineHeight;
    
    DrawText
    (
        TextFormat
        (
            "idle %s | nod %s | shake %s", 
            flag(gestures.idle), 
            flag(gestures.nod), 
            flag(gestures.shakeHead)
        ), 
        x, 
        y, 
        fontSize, 
        RAYWHITE
    ); 
        
    y += lineHeight;
    
    DrawText
    (
        TextFormat
        (
            "waveL %s | waveR %s", 
            flag(gestures.waveLeft), 
            flag(gestures.waveRight)
        ),  
        x, 
        y, 
        fontSize, 
        RAYWHITE
    );
          
    y += lineHeight;

    DrawText
    (
        TextFormat
        (
            "kickL %s | kickR %s", 
            flag(gestures.kickLeft), 
            flag(gestures.kickRight)
        ),  
        x, 
        y, 
        fontSize, 
        RAYWHITE
    );
    
    y += lineHeight;

    DrawText
    (
        TextFormat
        (
            "jump %s | shrug %s | celebrate %s", 
            flag(gestures.jump), 
            flag(gestures.shrug),
            flag(gestures.celebrate)
        ),  
        x, 
        y, 
        fontSize, 
        RAYWHITE
    );

    y += lineHeight;

    DrawText
    (
        TextFormat
        (
            "crouch %s |", 
            flag(gestures.crouch)
        ),  
        x, 
        y, 
        fontSize, 
        RAYWHITE
    );
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
        case RobotState::Emotions::Idle: robotState.emotion = RobotState::Emotions::Happy; break;
        case RobotState::Emotions::Happy: robotState.emotion = RobotState::Emotions::Sad; break;
        case RobotState::Emotions::Sad: robotState.emotion = RobotState::Emotions::Angry; break;
        case RobotState::Emotions::Angry: robotState.emotion = RobotState::Emotions::Surprised; break;
        case RobotState::Emotions::Surprised: robotState.emotion = RobotState::Emotions::Idle; break;
    }
}

void Robot::ToggleSpeaking()
{
    robotState.speaking = !robotState.speaking;
}

RobotState::Gestures& Robot::GetGestures()
{
    return robotState.gestures;
}

void Robot::ToggleGesture(std::string gesture)
{
    if(gesture == "idle") 
    {
        robotState.gestures.idle = !robotState.gestures.idle;
    }
    
    if(gesture == "nod") 
    {
        robotState.gestures.nod = !robotState.gestures.nod;
    }
    
    if(gesture == "shakeHead") 
    {
        robotState.gestures.shakeHead = !robotState.gestures.shakeHead;
    }

    if(gesture == "waveLeft") 
    {
        robotState.gestures.waveLeft = !robotState.gestures.waveLeft;
    }
    
    if(gesture == "waveRight") 
    {
        robotState.gestures.waveRight = !robotState.gestures.waveRight;
    }
    
    if(gesture == "kickLeft") 
    {
        robotState.gestures.kickLeft = !robotState.gestures.kickLeft;
    }

    if(gesture == "kickRight") 
    {
        robotState.gestures.kickRight = !robotState.gestures.kickRight;
    }

    if(gesture == "jump") 
    {
        robotState.gestures.jump = !robotState.gestures.jump;
    }

    if(gesture == "shrug") 
    {
        robotState.gestures.shrug = !robotState.gestures.shrug;
    }

    if(gesture == "celebrate") 
    {
        robotState.gestures.celebrate = !robotState.gestures.celebrate;
    }

    if(gesture == "crouch")
    {
        robotState.gestures.crouch = !robotState.gestures.crouch;
    }
}

void Robot::Shutdown()
{
    body.Shutdown();
}
