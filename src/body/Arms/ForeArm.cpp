#include "Body/Arms/ForeArm.h"

ForeArm::ForeArm(BodyDimensions& dimensions, std::string side) :
	dimensions(dimensions),
	side(side),
	hand(dimensions, side)
{}

void ForeArm::Initialise(){}
void ForeArm::Update(float dt){}
void ForeArm::Draw() const {}

int ForeArm::GetFrame() const{}

void ForeArm::SetRotation(float rotation){}