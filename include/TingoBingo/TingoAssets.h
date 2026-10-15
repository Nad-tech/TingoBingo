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
    Vector3 GetShoulderDimensions();
    Vector3 GetHeadDimensions();
    Vector3 GetUpperArmDimensions();
    Vector3 GetForeArmDimensions();
    Vector3 GetElbowDimensions();
    Vector3 GetHandDimensions();
    Vector3 GetFingerDimensions();

    Model bodyShape{};
    Model pelvis{};
    Model thigh{};
    Model knee{};
    Model shin{};
    Model foot{};
    Model neck{};
    Model head{};
    Model shoulder{};
    Model upperArm{};
    Model elbow{};
    Model foreArm{};
    Model hand{};
    Model finger{};

};