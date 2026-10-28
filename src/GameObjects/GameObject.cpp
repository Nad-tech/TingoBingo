#include "GameObjects/GameObject.h"

GameObject::GameObject(){}

void GameObject::Initialise()
{
    object = LoadModel("assets/models/gameobjects/object.glb");
}

void GameObject::Update(float dt)
{
    (void)dt;
}

void GameObject::Draw()
{
    DrawModelEx(
        object,
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

void GameObject::ShutDown()
{
    UnloadModel(object);
}