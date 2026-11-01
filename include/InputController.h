#pragma once

class InputController {
public:
    void Initialise();
    void Update();
    bool IsConnected() const;

    float GetLeftStickX() const { return leftStickX; }
    float GetLeftStickY() const { return leftStickY; }

    float GetRightStickX() const { return rightStickX; }
    float GetRightStickY() const { return rightStickY; }

private:
    bool connected = false;

    float leftStickX = 0.0f;
    float leftStickY = 0.0f;
    float rightStickX = 0.0f;
    float rightStickY = 0.0f;
};