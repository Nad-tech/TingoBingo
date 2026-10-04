#include "Body\Head\Eyes.h"

Eyes::Eyes(BodyDimensions& dimensions, RobotState& robotState) :
        dimensions(dimensions),
        robotState(robotState),
        leftEye(dimensions, "left", robotState),
        rightEye(dimensions, "right", robotState)
{}
        
void Eyes::Initialise()
{
    leftEye.Initialise();
    rightEye.Initialise();
}

void Eyes::ShutDown()
{
    leftEye.ShutDown();
    rightEye.ShutDown();
}

void Eyes::Update(float dt)
{
    Blink(dt);
    leftEye.Update(dt);
    rightEye.Update(dt);
}

void Eyes::Draw() const
{
    leftEye.Draw();
    rightEye.Draw();
}

void Eyes::SetTransform(MyTransform parentTransform)
{
    leftEye.SetTransform(parentTransform);
    rightEye.SetTransform(parentTransform);
}

void Eyes::Blink(float dt)
{
    blinkTimer += dt;

    if (blinkTimer > nextBlink)
    {
        leftEye.Blink();
        rightEye.Blink();

        blinkTimer = 0.0f;
        nextBlink = GetRandomValue(1000, 5000) / 1000.0f;
    }
}