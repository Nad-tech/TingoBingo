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
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);
}