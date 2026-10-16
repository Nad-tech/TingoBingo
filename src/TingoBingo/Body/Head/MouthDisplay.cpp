#include "TingoBingo/Body/Head/MouthDisplay.h"
#include "raymath.h"

MouthDisplay::MouthDisplay(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void MouthDisplay::Initialise()
{
    float Yoffset = -dimensions.mouthDisplay.height / 2.0f - 
                    0.2f + dimensions.head.height / 2.0f;

    positionOffset = {
        0.0f,
        Yoffset,
        dimensions.head.length / 2.0f + dimensions.mouthDisplay.length / 2.0f        
    };
}

void MouthDisplay::Update(float dt)
{
    (void)dt;
}

void MouthDisplay::Draw()
{
    DrawModelEx(
        assets.mouthDisplay,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );
}

void MouthDisplay::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = dimensions.scale;

    transform = MakeChildTransform(parentTransform, localTransform);
}