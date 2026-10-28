#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"

class Pupil
{
public:
Pupil(TingoAssets& assets, TingoDimensions& dimensions);

void Initialise();

void Update(float dt);
void Draw();

void SetTransform(MyTransform3D parentTransform);

void SetGazeTarget(Vector2 target);

private:
TingoAssets& assets;
TingoDimensions& dimensions;

Vector3 positionOffset;

// Current and desired pupil positions within the eye.
Vector2 gazeOffset = {0.0f, 0.0f};
Vector2 targetGazeOffset = {0.0f, 0.0f};

// Controls how quickly the pupil moves towards its target.
float gazeSpeed;

// Limits pupil movement to keep it inside the eye.
float maxGazeX = 0.0f;
float maxGazeY = 0.0f;

MyTransform3D transform;
};
