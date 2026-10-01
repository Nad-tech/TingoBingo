#include "Body/Head/Pupils.h"
#include "raylib.h"
#include "cmath"
#include "raymath.h"

Pupils::Pupils(BodyDimensions& dimensions) : 
    dimensions(dimensions),
    transform(),
    leftPupil(dimensions),
    rightPupil(dimensions)
{}

void Pupils::Initialise()
{
    leftPupil.SetSide("left");
    leftPupil.Initialise();
   
    rightPupil.SetSide("right");
    rightPupil.Initialise();
}

void Pupils::Shutdown()
{
    leftPupil.Shutdown();
    rightPupil.Shutdown();
}

void Pupils::Update(float dt, Emotion emotion)
{
    leftPupil.Update(dt, emotion);
    rightPupil.Update(dt, emotion);
}

void Pupils::Draw() const
{
    leftPupil.Draw();
    rightPupil.Draw();
}

void Pupils::SetTransform(MyTransform parentTransform)
{
    transform = parentTransform;

    leftPupil.SetTransform(parentTransform);
    rightPupil.SetTransform(parentTransform);

    SetRotation(transform.rotation);
}

Vector2 Pupils::RotateVector(Vector2 v, float rotation)
{
    float r = rotation * DEG2RAD;

    return
    {
        v.x * cosf(r) - v.y * sinf(r),
        v.x * sinf(r) + v.y * cosf(r)
    };
}

void Pupils::SetRotation(float rotation)
{
    Vector2 rotatedLeft =
        RotateVector(leftLookOffset, rotation);

    Vector2 rotatedRight =
        RotateVector(rightLookOffset, rotation);

    leftPupil.SetRotation(rotation);
    rightPupil.SetRotation(rotation);

    leftPupil.SetPosition(
    {
        transform.position.x + rotatedLeft.x,
        transform.position.y + rotatedLeft.y
    });

    rightPupil.SetPosition(
    {
        transform.position.x + rotatedRight.x,
        transform.position.y + rotatedRight.y
    });
}

void Pupils::LookAt(Vector2 point)
{
    float scale = transform.scale;

    Vector2 leftEyeCentre =
    {
        transform.position.x + leftPupil.GetSideOffset() * scale,
        transform.position.y -
        (dimensions.bodyHeight / 2 
        + dimensions.headHeight / 2 
        + dimensions.neckHeight 
        + dimensions.eyesYoffset) * scale

    };

    Vector2 rightEyeCentre =
    {
        transform.position.x - rightPupil.GetSideOffset() * scale,
        transform.position.y -  
        (dimensions.bodyHeight / 2 
        + dimensions.headHeight / 2 
        + dimensions.neckHeight 
        + dimensions.eyesYoffset) * scale
    };

    Vector2 leftDirection =
    {
        point.x - leftEyeCentre.x,
        point.y - leftEyeCentre.y
    };

    Vector2 rightDirection =
    {
        point.x - rightEyeCentre.x,
        point.y - rightEyeCentre.y
    };

    leftDirection = Vector2Normalize(leftDirection);
    rightDirection = Vector2Normalize(rightDirection);

    leftLookOffset =
    {
        leftDirection.x * LOOK_DISTANCE,
        leftDirection.y * LOOK_DISTANCE
    };

    rightLookOffset =
    {
        rightDirection.x * LOOK_DISTANCE,
        rightDirection.y * LOOK_DISTANCE
    };

    SetRotation(transform.rotation);
}

void Pupils::LookForward()
{
    leftLookOffset = {0.0f, 0.0f};
    rightLookOffset = {0.0f, 0.0f};

    leftPupil.SetPosition(
    {
        transform.position.x,
        transform.position.y
    });

    rightPupil.SetPosition(
    {
        transform.position.x,
        transform.position.y
    });
}
