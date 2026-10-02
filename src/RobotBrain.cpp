#include "RobotBrain.h"
#include "Robot.h"
#include "BodyDimensions.h"
#include "raylib.h"

RobotBrain::RobotBrain(Robot& robot, RobotState& robotState) : 
    robot(robot),
    robotState(robotState)
{}

void RobotBrain::Update(float dt)
{
    
}

void RobotBrain::Draw() const
{

}


