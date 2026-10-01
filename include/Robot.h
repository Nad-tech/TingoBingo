#pragma once

#include "RobotBrain.h"
#include "Emotion.h"
#include "Body/Body.h"
#include "BodyDimensions.h"
#include "MyTransform.h"

class Robot
{
public:
    Robot();
    void Initialise();
    void Shutdown();
    
    void Update(float dt);
    void Draw() const;
    
    void SetTransform(MyTransform transform);
    
    void SetEmotion(Emotion emotion);
    Emotion GetEmotion();
    
    
private:
    BodyDimensions dimensions;
    MyTransform transform;
   
    Body body;
    RobotBrain robotBrain;
};