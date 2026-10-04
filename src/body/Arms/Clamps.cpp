#include "body/Arms/Clamps.h"

Clamps::Clamps(BodyDimensions& dimensions, RobotState& robotState) :
    dimensions(dimensions),
    robotState(robotState),
    upperFinger(dimensions, "upper", robotState),
    lowerFinger(dimensions, "lower", robotState)
{}

void Clamps::Initialise(){}
void Clamps::Shutdown(){};

void Clamps::Update(float dt){}
void Clamps::Draw() const{}
        
void Clamps::SetTransform(MyTransform parentTransform){}