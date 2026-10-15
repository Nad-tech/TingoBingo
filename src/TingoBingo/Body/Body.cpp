#include "TingoBingo/Body/Body.h"

Body::Body(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    pelvis(assets, dimensions),
    neck(assets, dimensions)
{}

void Body::Initialise()
{
    pelvis.Initialise();
    neck.Initialise();
}

void Body::ShutDown()
{
}

void Body::Update(float dt)
{
    pelvis.Update(dt);
    neck.Update(dt);
}

void Body::Draw()
{
    DrawModelEx(
        assets.bodyShape,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.bodyShape,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    pelvis.Draw();
    neck.Draw();
}

void Body::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    pelvis.SetTransform(transform);
    neck.SetTransform(transform);
}