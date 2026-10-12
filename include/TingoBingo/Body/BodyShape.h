#pragma once

#include "MyTransform3D.h"

class BodyShape
{
public:
    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D initialTransform);

private:
    MyTransform3D transform;
};