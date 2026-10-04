#include "Body\Head\Eyes.h"

Eyes::Eyes(BodyDimensions& dimensions, RobotState& robotState) :
        dimensions(dimensions),
        robotState(robotState),
        leftEye(dimensions, "left", robotState),
        rightEye(dimensions, "right", robotState)
{}
        
void Eyes::Initialise()
{

}

void Eyes::Shutdown()
{

}

void Eyes::Update(float dt)
{

}

void Eyes::Draw() const
{

}

void Eyes::SetTransform(MyTransform parentTransform)
{
        
}