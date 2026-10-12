#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/Body/Body.h"

class Tingo
{
public:
    void Initialise();
    void ShutDown();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D initialTransform);

private:
    MyTransform3D transform;
    Body body;
};