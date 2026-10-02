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


class Body
{
public:
    Body(BodyDimensions& dimensions, RobotState& robotState);
    void Initialise();
    void Shutdown();
    
    void Update(float dt);
    void Draw() const;
    
    void SetTransform(MyTransform transform);

private:
    BodyDimensions &dimensions;
    MyTransform transform;
    RobotState& robotState;
    
    BodyBase bodyBase;
    Neck neck;
    Pelvis pelvis;
    Arms arms;

};
