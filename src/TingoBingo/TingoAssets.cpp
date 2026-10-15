#include "TingoBingo/TingoAssets.h"
#include "raymath.h"

void TingoAssets::Initialise()
{
    bodyShape = LoadModel("assets/models/tingo/Body.glb");
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
}

Vector3 TingoAssets::GetBodyDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(bodyShape);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetPelvisDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(pelvis);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetThighDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(thigh);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetKneeDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(knee);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetShinDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(shin);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetFootDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(foot);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetNeckDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(neck);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetShoulderDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(shoulder);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetHeadDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(head);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetUpperArmDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(upperArm);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetForeArmDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(foreArm);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetElbowDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(elbow);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetHandDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(hand);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

Vector3 TingoAssets::GetFingerDimensions()
{
    BoundingBox bounds = GetModelBoundingBox(finger);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

void TingoAssets::ShutDown()
{
    UnloadModel(bodyShape);
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
}
