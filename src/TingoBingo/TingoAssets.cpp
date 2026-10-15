#include "TingoBingo/TingoAssets.h"
#include "raymath.h"

void TingoAssets::Initialise()
{
    bodyShape = LoadModel("assets/models/tingo/Body.glb");
    pelvis = LoadModel("assets/models/tingo/pelvis.glb");
    thigh = LoadModel("assets/models/tingo/thigh.glb");
    knee = LoadModel("assets/models/tingo/knee.glb");
    shin = LoadModel("assets/models/tingo/shin.glb");
    foot = LoadModel("assets/models/tingo/foot.glb");
    neck = LoadModel("assets/models/tingo/neck.glb");
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

void TingoAssets::ShutDown()
{
    UnloadModel(bodyShape);
    UnloadModel(pelvis);
    UnloadModel(thigh);
    UnloadModel(knee);
    UnloadModel(shin);
    UnloadModel(foot);
    UnloadModel(neck);
}
