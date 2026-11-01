#include "InputController.h"
#include "raylib.h"

void InputController::Initialise()
{
    connected = IsGamepadAvailable(0);
}

void InputController::Update()
{
    connected = IsGamepadAvailable(0);

    if (!connected)
        return;

    leftStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_X);
    leftStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_LEFT_Y);

    rightStickX = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_X);
    rightStickY = GetGamepadAxisMovement(0, GAMEPAD_AXIS_RIGHT_Y);
}

bool InputController::IsConnected() const
{
    return connected;
}