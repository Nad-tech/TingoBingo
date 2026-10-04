#include "Body\Head\Eye.h"

Eye::Eye(BodyDimensions& dimensions, std::string side, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    pupil(dimensions, robotState)
{}

void Eye::Initialise(){}
void Eye::Shutdown(){}
void Eye::Update(float dt){}
void Eye::Draw() const{}
void Eye::SetTransform(MyTransform parentTransform){}