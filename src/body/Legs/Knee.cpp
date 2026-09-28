#include "Body/Legs/Knee.h"

Knee::Knee(BodyDimensions& dimensions) :
	dimensions(dimensions),
	shin(dimensions)
{}

void Knee::Initialise(){}
void Knee::Update(float dt){}
void Knee::Draw() const{}
void Knee::SetRotation(float rotation){}
void Knee::SetAnchorPoint(Vector2 anchorPoint){}
void Knee::Shutdown(){}