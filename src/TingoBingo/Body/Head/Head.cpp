#include "TingoBingo/Body/Head/Head.h"
#include "raymath.h"
#include <iostream>

Head::Head
(
    TingoAssets& assets, 
    TingoDimensions& dimensions,
    TingoState& state
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    mouthDisplay(assets, dimensions, state),
    leftEye(assets, dimensions, state, "left"),
    rightEye(assets, dimensions, state, "right"),
    nose(assets, dimensions),
    leftEyeBrow(assets, dimensions, "left"),
    rightEyeBrow(assets, dimensions, "right"),
    leftEar(assets, dimensions, "left"),
    rightEar(assets, dimensions, "right"),
    antenna(assets, dimensions)
{}

void Head::Initialise()
{
    positionOffset = {
        0.0f,
        dimensions.neck.height / 2.0f,
        0.0f        
    };

    mouthDisplay.Initialise();
    leftEye.Initialise();
    rightEye.Initialise();
    nose.Initialise();
    leftEyeBrow.Initialise();
    rightEyeBrow.Initialise();
    leftEar.Initialise();
    rightEar.Initialise();
    antenna.Initialise();
}

void Head::Update(float dt)
{
    mouthDisplay.Update(dt);
    leftEye.Update(dt);
    rightEye.Update(dt);

    //localRotation += dt * 40;
}

void Head::Draw()
{
    DrawModelEx(
        assets.head,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    mouthDisplay.Draw();
    leftEye.Draw();
    rightEye.Draw();
    nose.Draw();
    leftEyeBrow.Draw();
    rightEyeBrow.Draw();
    leftEar.Draw();
    rightEar.Draw();
    antenna.Draw();
}

void Head::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    
    // Horizontal rotation (yaw).
    Quaternion yaw = QuaternionFromAxisAngle(
        {0.0f, 1.0f, 0.0f},
        localYaw * DEG2RAD
    );

    // Vertical rotation (pitch).
    Quaternion pitch = QuaternionFromAxisAngle(
        {1.0f, 0.0f, 0.0f},
        localPitch * DEG2RAD
    );

    // Combine the rotations.
    Quaternion combinedRotation = QuaternionMultiply(yaw, pitch);

    // Convert quaternion to axis-angle.
    Vector3 axis;
    float angle;

    QuaternionToAxisAngle(
        combinedRotation,
        &axis,
        &angle
    );

    localTransform.rotationAxis = axis;
    localTransform.rotationAngle = angle * RAD2DEG;
    
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);

    mouthDisplay.SetTransform(transform);
    leftEye.SetTransform(transform);
    rightEye.SetTransform(transform);
    nose.SetTransform(transform);
    leftEyeBrow.SetTransform(transform);
    rightEyeBrow.SetTransform(transform);
    leftEar.SetTransform(transform);
    rightEar.SetTransform(transform);
    antenna.SetTransform(transform);
}

EyeState Head::GetLeftEyeState() const
{
    return leftEye.GetEyeState();
}

EyeState Head::GetRightEyeState() const
{
    return rightEye.GetEyeState();
}

void Head::SetGazeTarget(Vector2 target)
{
    leftEye.SetGazeTarget(target);
    rightEye.SetGazeTarget(target);
}

const MyTransform3D& Head::GetTransform() const
{
    return transform;
}

Vector3 Head::GetForwardDirection() const
{
    Quaternion rotation = QuaternionFromAxisAngle(
        transform.rotationAxis,
        transform.rotationAngle * DEG2RAD
    );

    return Vector3Normalize(
        Vector3RotateByQuaternion(
            { 0.0f, 0.0f, 1.0f },
            rotation
        )
    );
}

Vector3 Head::GetVisionPosition() const
{
    Vector3 leftPosition = leftEye.GetTransform().position;
    Vector3 rightPosition = rightEye.GetTransform().position;

    return Vector3Scale(
        Vector3Add(leftPosition, rightPosition),
        0.5f
    );
}

void Head::SetLocalYaw(float yaw)
{
    localYaw = yaw;
}

float Head::GetLocalYaw()
{
    return localYaw;
}

void Head::SetLocalPitch(float pitch)
{
    localPitch = pitch;
}

float Head::GetLocalPitch()
{
    return localPitch;
}