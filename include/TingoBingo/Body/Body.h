#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/Body/BodyShape.h"

class Body
{
public:
    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D initialTransform);

private:
    MyTransform3D transform;
    BodyShape bodyShape;
};