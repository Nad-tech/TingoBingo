#include "Body/Arms/Hand.h"

Hand::Hand(BodyDimensions& dimensions, std::string side) :
	dimensions(dimensions),
	side(side)
{}

void Hand::Initialise(){}
void Hand::Update(float dt){}
void Hand::Draw() const {}
        
int Hand::GetFrame() const{}
        
void Hand::SetRotation(float rotation){}