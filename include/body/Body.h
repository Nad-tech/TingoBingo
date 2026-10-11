#pragma once

#include "raylib.h"
#include "BodyBase.h"
#include "Body/Arms/Arms.h"
#include "Body/Pelvis.h"
#include "Body/Head/Head.h"
#include "Body/Neck.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
#include "RobotState.h"
#include "Body/Head/Head.h"


class Body
{
public:
    enum class CrouchState
    {
        None,
        Lowering,
        Crouching,
        Returning
    };

    Body(BodyDimensions& dimensions, RobotState& robotState);
    void Initialise();
    void Shutdown();
    
    void Update(float dt);
    void Draw() const;
    
    void SetTransform(MyTransform parentTransform);

    void Crouch();

    void LookAt(Vector2 point);

    Head& GetHead();

private:
    void AdvanceCrouch(float dt);

    BodyDimensions &dimensions;
    MyTransform transform;
    RobotState& robotState;
    
    BodyBase bodyBase;
    Neck neck;
    Pelvis pelvis;
    Arms arms;

    CrouchState crouchState = CrouchState::None;
    MyTransform tempParentTransform;
    float crouchOffsetY = 0.0f;

};
