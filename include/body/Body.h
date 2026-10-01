#pragma once

#include "raylib.h"
#include "Emotion.h"
#include "BodyBase.h"
#include "Body/Arms/Arms.h"
#include "Body/Pelvis.h"
#include "Body/Head/Head.h"
#include "Body/Neck.h"
#include "BodyDimensions.h"
#include "MyTransform.h"


class Body
{
public:
    Body(BodyDimensions& dimensions);
    void Initialise();
    void Shutdown();
    
    void Update(float dt, Emotion emotion);
    void Draw() const;
    
    void SetTransform(MyTransform transform);

private:
    BodyDimensions &dimensions;
    MyTransform transform;
    BodyBase bodyBase;
    Neck neck;
    Pelvis pelvis;
    Arms arms;
};
