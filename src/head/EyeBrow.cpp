#include "Body\Head\EyeBrow.h"

EyeBrow::EyeBrow(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState)
{}
        
void EyeBrow::Initialise(){}
void EyeBrow::Shutdown(){}
void EyeBrow::Update(float dt){}
void EyeBrow::Draw() const{}
void EyeBrow::SetTransform(MyTransform parentTransform){}
