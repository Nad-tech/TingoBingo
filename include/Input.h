#pragma once

#include "raylib.h"
class Input
{
public:
    bool LeftPressed() const;
    bool RightPressed() const;
    bool SpacePressed() const;
    Vector2 MousePosition() const;
  
    bool LeftMouseButtonPressed() const;
    bool G_Pressed() const;

    bool E_Pressed();
    bool S_Pressed();
};