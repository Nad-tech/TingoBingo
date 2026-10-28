#pragma once

#include "MyTransform3D.h"
#include "TingoBingo/TingoDimensions.h"
#include "TingoBingo/TingoAssets.h"

class GameObject
{
public:
    GameObject();

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D transform);

    void ShutDown();

private:

    Model object;
    
    MyTransform3D transform;
};