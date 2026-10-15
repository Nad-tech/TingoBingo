#pragma once

#include "raylib.h"

class TingoAssets {
public:
    void Initialise();
    void ShutDown();

    Vector3 GetBodyDimensions();
    Vector3 GetPelvisDimensions();
    Vector3 GetThighDimensions();
    Vector3 GetKneeDimensions();
    Vector3 GetShinDimensions();
    Vector3 GetFootDimensions();
    Vector3 GetNeckDimensions();

    Model bodyShape{};
    Model pelvis{};
    Model thigh{};
    Model knee{};
    Model shin{};
    Model foot{};
    Model neck{};
};