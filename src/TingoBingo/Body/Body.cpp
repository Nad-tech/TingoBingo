#include "TingoBingo/Body/Body.h"

Body::Body
(
    TingoAssets& assets, 
    TingoDimensions& dimensions, 
    TingoState& state
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    pelvis(assets, dimensions, state),
    neck(assets, dimensions, state),
    leftShoulder(assets, dimensions, state, "left"),
    rightShoulder(assets, dimensions, state, "right")
{}

void Body::Initialise()
{
    positionOffset = {0.0f, 0.0f, 0.0f};

    pelvis.Initialise();
    neck.Initialise();
    leftShoulder.Initialise();
    rightShoulder.Initialise();

    maxThighSwing = 20.0f;
    walkSpeed = 5.0f;
    walkPhase = 0.0f;
    thighReturnSpeed = walkSpeed;
}

void Body::Update(float dt)
{
    AdvanceWalk(dt);

    pelvis.Update(dt);
    neck.Update(dt);
    leftShoulder.Update(dt);
    rightShoulder.Update(dt);
}

void Body::Draw()
{
    DrawModelEx(
        assets.body,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    pelvis.Draw();
    neck.Draw();
    leftShoulder.Draw();
    rightShoulder.Draw();
}

void Body::SetTransform(MyTransform3D parentTransform)
{   
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    pelvis.SetTransform(transform);
    neck.SetTransform(transform);
    leftShoulder.SetTransform(transform);
    rightShoulder.SetTransform(transform);
}

ArmWaveState Body::GetLeftArmWaveState() const
{
    return leftShoulder.GetWaveState();
}

ArmWaveState Body::GetRightArmWaveState() const
{
    return rightShoulder.GetWaveState();
}

EyeState Body::GetLeftEyeState() const
{
    return neck.GetLeftEyeState();
}

EyeState Body::GetRightEyeState() const
{
    return neck.GetRightEyeState();
}

void Body::SetGazeTarget(Vector2 target)
{
    neck.SetGazeTarget(target);
}

Vector3 Body::GetVisionPosition() const
{
    return neck.GetVisionPosition();
}

Vector3 Body::GetHeadForwardDirection() const
{
    return neck.GetHeadForwardDirection();
}

Neck& Body::GetNeck()
{
    return neck;
}

void Body::AdvanceWalk(float dt)
{
    if(state.walkState == TingoState::WalkState::Walking)
    {
        walkPhase += dt * walkSpeed * state.walkSpeedScale;

        //Move legs
        float leftThighAngle = sinf(walkPhase) * maxThighSwing;
        float rightThighAngle = sinf(walkPhase + PI) * maxThighSwing;

        pelvis.SetLeftThighLocalRotation(leftThighAngle);
        pelvis.SetRightThighLocalRotation(rightThighAngle);

        //Move arms opposing legs
        leftShoulder.SetLocalRotation(rightThighAngle);
        rightShoulder.SetLocalRotation(leftThighAngle);
    }
    else
    {
        float returnAmount = Clamp(
            thighReturnSpeed * dt,
            0.0f,
            1.0f
        );

        float leftRotation = 
            pelvis.GetLeftThighLocalRotation();

        float rightRotation = 
            pelvis.GetRightThighLocalRotation();

        leftRotation = Lerp(leftRotation, 0.0f, returnAmount);
        rightRotation = Lerp(rightRotation, 0.0f, returnAmount);

        pelvis.SetLeftThighLocalRotation(leftRotation);
        pelvis.SetRightThighLocalRotation(rightRotation);

        leftShoulder.SetLocalRotation(rightRotation);
        rightShoulder.SetLocalRotation(leftRotation);
    }
}