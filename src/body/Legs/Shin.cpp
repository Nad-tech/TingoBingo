#include "Body/Legs/Shin.h"

Shin::Shin(BodyDimensions& dimensions) :
	dimensions(dimensions),
	foot(dimensions)
{}

void Shin::Initialise(){}
void Shin::Update(float dt){}
void Shin::Draw() const{}
void Shin::SetRotation(float rotation){}
void Shin::SetAnchorPoint(Vector2 anchorPoint){}
void Shin::Shutdown(){}