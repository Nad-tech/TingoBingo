#include "Body\Head\EyeBrows.h"

EyeBrows::EyeBrows(BodyDimensions& dimensions, RobotState& robotState) :
        dimensions(dimensions),
        robotState(robotState),
        leftEyeBrow(dimensions, "left", robotState),
        rightEyeBrow(dimensions, "right", robotState)
{}
        
void EyeBrows::Initialise()
{

}

void EyeBrows::ShutDown()
{

}

void EyeBrows::Update(float dt)
{

}

void EyeBrows::Draw() const
{

}

void EyeBrows::SetTransform(MyTransform parentTransform)
{
        
}