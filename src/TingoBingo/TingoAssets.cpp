#include "TingoBingo/TingoAssets.h"
#include "raymath.h"

inline Vector3 GetDimensions(Model model)
{
    BoundingBox bounds = GetModelBoundingBox(model);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

void TingoAssets::Initialise()
{
    body = LoadModel("assets/models/tingo/Body.glb");
    pelvis = LoadModel("assets/models/tingo/Pelvis.glb");
    thigh = LoadModel("assets/models/tingo/Thigh.glb");
    knee = LoadModel("assets/models/tingo/Knee.glb");
    shin = LoadModel("assets/models/tingo/Shin.glb");
    foot = LoadModel("assets/models/tingo/Foot.glb");
    neck = LoadModel("assets/models/tingo/Neck.glb");
    shoulder = LoadModel("assets/models/tingo/Shoulder.glb");
    head = LoadModel("assets/models/tingo/Head.glb");
    upperArm = LoadModel("assets/models/tingo/UpperArm.glb");
    elbow = LoadModel("assets/models/tingo/Elbow.glb");
    foreArm = LoadModel("assets/models/tingo/ForeArm.glb");
    hand = LoadModel("assets/models/tingo/Hand.glb");
    finger = LoadModel("assets/models/tingo/Finger.glb");
    mouthDisplay = LoadModel("assets/models/tingo/MouthDisplay.glb");
    eye = LoadModel("assets/models/tingo/Eye.glb");
    pupil = LoadModel("assets/models/tingo/Pupil.glb");
    nose = LoadModel("assets/models/tingo/Nose.glb");
    eyeBrow = LoadModel("assets/models/tingo/EyeBrow.glb");
}

Vector3 TingoAssets::GetBodyDimensions()
{
    return GetDimensions(body);
}

Vector3 TingoAssets::GetPelvisDimensions()
{
    return GetDimensions(pelvis);
}

Vector3 TingoAssets::GetThighDimensions()
{
    return GetDimensions(thigh);
}

Vector3 TingoAssets::GetKneeDimensions()
{
    return GetDimensions(knee);
}


Vector3 TingoAssets::GetShinDimensions()
{
    return GetDimensions(shin);
}

Vector3 TingoAssets::GetFootDimensions()
{
    return GetDimensions(foot);
}

Vector3 TingoAssets::GetNeckDimensions()
{
    return GetDimensions(neck);
}

Vector3 TingoAssets::GetShoulderDimensions()
{
    return GetDimensions(shoulder);
}

Vector3 TingoAssets::GetHeadDimensions()
{
    return GetDimensions(head);
}

Vector3 TingoAssets::GetUpperArmDimensions()
{
    return GetDimensions(upperArm);
}

Vector3 TingoAssets::GetForeArmDimensions()
{
    return GetDimensions(foreArm);
}

Vector3 TingoAssets::GetElbowDimensions()
{
    return GetDimensions(elbow);
}

Vector3 TingoAssets::GetHandDimensions()
{
    return GetDimensions(hand);
}

Vector3 TingoAssets::GetFingerDimensions()
{
    return GetDimensions(finger);
}

Vector3 TingoAssets::GetMouthDisplayDimensions()
{
    return GetDimensions(mouthDisplay);
}

Vector3 TingoAssets::GetEyeDimesnsions()
{
    return GetDimensions(eye);
}

Vector3 TingoAssets::GetPupilDimensions()
{
    return GetDimensions(pupil);
}

Vector3 TingoAssets::GetNoseDimensions()
{
    return GetDimensions(nose);
}

Vector3 TingoAssets::GetEyeBrowDimensions()
{
    return GetDimensions(eyeBrow);
}

void TingoAssets::ShutDown()
{
    UnloadModel(body);
    UnloadModel(pelvis);
    UnloadModel(thigh);
    UnloadModel(knee);
    UnloadModel(shin);
    UnloadModel(foot);
    UnloadModel(neck);
    UnloadModel(head);
    UnloadModel(shoulder);
    UnloadModel(upperArm);
    UnloadModel(foreArm);
    UnloadModel(elbow);
    UnloadModel(hand);
    UnloadModel(finger);
    UnloadModel(mouthDisplay);
    UnloadModel(eye);
    UnloadModel(pupil);
    UnloadModel(nose);
    UnloadModel(eyeBrow);
}
