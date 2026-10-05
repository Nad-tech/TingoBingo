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
    if(wasLeftEyeClosed && !robotState.gestures.closeLeftEye) leftEye.Open();
    if(wasRightEyeClosed && !robotState.gestures.closeRightEye) rightEye.Open();

    CloseLeft(dt);
    CloseRight(dt);

    wasLeftEyeClosed = robotState.gestures.closeLeftEye;
    wasRightEyeClosed = robotState.gestures.closeRightEye;

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
        if(!robotState.gestures.closeLeftEye) leftEye.Blink();
        if(!robotState.gestures.closeRightEye) rightEye.Blink();

        blinkTimer = 0.0f;
        nextBlink = GetRandomValue(1000, 5000) / 1000.0f;
    }
}

void Eyes::CloseLeft(float dt)
{
    if(robotState.gestures.closeLeftEye) leftEye.Close();
    else Blink(dt);
}

void Eyes::CloseRight(float dt)
{
    if(robotState.gestures.closeRightEye) rightEye.Close();
    else Blink(dt);
}
