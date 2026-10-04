#include "Body\Arms\Finger.h"

Finger::Finger
(
    BodyDimensions& dimensions, 
    std::string side,
    RobotState& robotState
) : 
    dimensions(dimensions),
    robotState(robotState)
{}
        
void Finger::Initialise(){}
        
void Finger::Update(float dt){}
void Finger::Draw() const{}
        
void Finger::SetTransform(MyTransform parentTransform){}