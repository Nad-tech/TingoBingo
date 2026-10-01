#include "GestureController.h"

GestureController::GestureController(Body& body):
    body(body)
{}

void GestureController::SetGesture(Gesture gesture)
{
    currentGesture = gesture;
    gestureTimer = 0.0f;
    playing = true;
}

void GestureController::Update(float dt)
{
    if (!playing)
        return;

    gestureTimer += dt;

    switch (currentGesture)
    {
        case Gesture::Wave:

            break;

        default:
            break;
    }
}