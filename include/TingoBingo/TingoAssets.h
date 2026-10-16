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
    Vector3 GetMouthDisplayDimensions();
    Vector3 GetEyeDimesnsions();
    Vector3 GetPupilDimensions();
    Vector3 GetNoseDimensions();
    Vector3 GetEyeBrowDimensions();
    Vector3 GetEarDimensions();

    Model body{};
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
    Model mouthDisplay{};
    Model eye{};
    Model pupil{};
    Model nose{};
    Model eyeBrow{};
    Model ear{};

    // Shared lighting shader.
    Shader lightingShader{};

    // Shader uniform locations.
    int lightDirectionLoc = -1;
    int ambientLoc = -1;
    int viewPositionLoc = -1;

    // Update the lighting using the current camera position.
    void UpdateLighting(Vector3 cameraPosition);
};