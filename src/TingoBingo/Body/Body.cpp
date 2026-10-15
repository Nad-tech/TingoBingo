#include "TingoBingo/Body/Body.h"

Body::Body(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    pelvis(assets, dimensions),
    neck(assets, dimensions),
    leftShoulder(assets, dimensions, "left"),
    rightShoulder(assets, dimensions, "right"),
    head(assets, dimensions)
{}

void Body::Initialise()
{
    positionOffset = {0.0f, 0.0f, 0.0f};

    pelvis.Initialise();
    neck.Initialise();
    leftShoulder.Initialise();
    rightShoulder.Initialise();
    head.Initialise();
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
    leftShoulder.Draw();
    rightShoulder.Draw();
    head.Draw();
}

void Body::SetTransform(MyTransform3D parentTransform)
{   
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
    
    pelvis.SetTransform(transform);
    neck.SetTransform(transform);
    leftShoulder.SetTransform(transform);
    rightShoulder.SetTransform(transform);
    head.SetTransform(transform);
}