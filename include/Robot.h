#pragma once

#include "RobotBrain.h"
#include "Body/Body.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
#include "RobotState.h"
#include "Body/Head/Head.h"

class Robot
{
public:
    Robot();
    void Initialise();
    void Shutdown();
    
    void Update(float dt);
    void Draw() const;
    
    void SetTransform(MyTransform initialTransform);

    void CycleState();
    void CycleEmotion();
    void CycleSearchType();
    void CycleSearchPhase();
    void ToggleSpeaking();
    void ToggleGesture(std::string gesture);
   
    RobotState::Gestures& GetGestures();

    RobotBrain& GetRobotBrain();

    void LookAt(Vector2 point);

    Head& GetHead();
    
private:
    BodyDimensions dimensions;
    MyTransform transform;
   
    RobotState robotState;

    Body body;
    RobotBrain robotBrain;
};
