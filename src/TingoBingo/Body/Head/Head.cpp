#include "TingoBingo/Body/Head/Head.h"
#include "raymath.h"

Head::Head(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void Head::Initialise()
{
    positionOffset = {
        0.0f,
        dimensions.bodyShape.height / 2.0f +
        dimensions.neck.height +
        dimensions.head.height / 2.0f,
        0.0f        
    };
}

void Head::ShutDown()
{
    
}

void Head::Update(float dt)
{
    (void)dt;
}

void Head::Draw()
{
    DrawModelEx(
        assets.head,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.head,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );
}

void Head::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
}