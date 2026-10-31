#include "GameObjects/GameObject.h"

GameObject::GameObject(GameObjectAssets& gameAssets) :
    gameAssets(gameAssets)
{}

void GameObject::Initialise()
{
    
}

void GameObject::Update(float dt)
{
    (void)dt;
}

void GameObject::Draw()
{
    DrawModelEx(
        gameAssets.object,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void GameObject::SetTransform(MyTransform3D transform)
{
    this->transform = transform;
}