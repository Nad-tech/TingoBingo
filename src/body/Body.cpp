#include "Body/Body.h"
#include <cmath>
#include "Emotion.h"

Body::Body(BodyDimensions& dimensions) :
    dimensions(dimensions),
    bodyBase(dimensions),
    neck(dimensions),
    pelvis(dimensions),
    arms(dimensions)
{}

void Body::Initialise()
{
    bodyBase.Initialise();
    neck.Initialise();
    arms.Initialise();
    pelvis.Initialise();
}

void Body::Shutdown()
{
    neck.Shutdown();
    arms.Shutdown();
    pelvis.Shutdown();
}

void Body::Update(float dt, Emotion emotion)
{
    neck.Update(dt, emotion);
    arms.Update(dt, emotion);
    pelvis.Update(dt, emotion);
}

void Body::Draw() const
{
    bodyBase.Draw();
    arms.Draw();
    neck.Draw();
    pelvis.Draw();
}

void Body::SetTransform(MyTransform transform)
{
    this->transform = transform;

    bodyBase.SetTransform(this->transform);
    neck.SetTransform(this->transform);
    arms.SetTransform(this->transform);
    pelvis.SetTransform(this->transform);
}