#include "GameObjects/GameObject.h"

GameObject::GameObject(
    Model& object, 
    std::string name,
    bool interactable) :
    object(object),
    name(name),
    interactable(interactable)
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

Vector3 GameObject::GetPosition() const
{
    return transform.position;
}

BoundingBox GameObject::GetBoundingBox() const
{
    BoundingBox bounds = GetModelBoundingBox(object);

    bounds.min = Vector3Add(
        Vector3Multiply(bounds.min, transform.scale),
        transform.position
    );

    bounds.max = Vector3Add(
        Vector3Multiply(bounds.max, transform.scale),
        transform.position
    );

    return bounds;
}

std::string GameObject::GetName() const
{
    return name;
}

bool GameObject::IsInteractable() const 
{
    return interactable;
}