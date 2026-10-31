#pragma once

#include "MyTransform3D.h"
#include "GameObjects/GameObjectAssets.h"

class GameObject
{
public:
    GameObject(GameObjectAssets& gameAssets);

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D transform);

private:
    GameObjectAssets& gameAssets;
    
    MyTransform3D transform;
};