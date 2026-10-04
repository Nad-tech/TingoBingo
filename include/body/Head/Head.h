#pragma once

#include "raylib.h"
#include "Body/Head/Antenna.h"
#include "Body/Head/Ears.h"
#include "Body/Head/Eyebrows.h"
#include "Body/Head/Mouth.h"
#include "Body/Head/Eyes.h"
#include "Body/Head/Headbase.h"
#include "Body/Head/Nose.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
#include "RobotState.h"

//====================================================
// Head
//
// Controls the complete robot head.
//
// Head owns all of the individual head components and
// keeps them synchronised so they behave as one unit.
//
// Facial features such as the eyes, mouth, eyebrows
// and pupils can animate independently while the
// Headbase handles the main head orientation.
//====================================================

class Head
{
public:
    enum class NodState
    {
        None,
        Raising,
        Lowering,
        Returning
    };

    enum class ShrugState
    {
        None,
        Lowering,
        Returning
    };
        
    Head(BodyDimensions& dimensions, RobotState& robotState);
    
    void Initialise();
    void Shutdown();
    
    void Update(float dt);
    void Draw() const;

    void SetTransform(MyTransform parentTransform);

    void LookAt(Vector2 point);
    void LookForward();
    
    void Nod();
    void Shrug();

private:
    void AdvanceNod(float dt);
    void AdvanceShrug(float dt);

    BodyDimensions& dimensions;
    
    MyTransform transform;
    MyTransform tempParentTransform;

    Vector2 positionOffset;
    
    RobotState& robotState;
    NodState nodState = NodState::None;
    ShrugState shrugState = ShrugState::None;
    float YOffset = 0.0f;

    Headbase headBase;
    Eyes eyes;
    Antenna antenna;
    Ears ears;
    EyeBrows eyebrows;
    Mouth mouth;
    Nose nose;
};