#pragma once

#include "MyTransform3D.h"
#include "GameObjects/GameObjectAssets.h"
#include <string>

class GameObject
{
public:
    GameObject(
        Model& object, 
        std::string name,
        bool interactable    
    );

    void Initialise();
    
    void Update(float dt);
    void Draw();

    void SetTransform(MyTransform3D transform);
    MyTransform3D& GetTransform();

    Vector3 GetPosition() const;
    BoundingBox GetBoundingBox() const;
    std::string GetName() const;
    bool IsInteractable() const;

private:
    Model& object;
    std::string name;
    bool interactable;
    
    MyTransform3D transform;
};