#include "TingoBingo/Body/Arm/ForeArm.h"
#include "raymath.h"

ForeArm::ForeArm(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    hand(assets, dimensions)
{}


void ForeArm::Initialise()
{
    positionOffset = {
        0.0f,
        -dimensions.elbow.height / 2.0f - dimensions.foreArm.height / 2.0f,
        0.0f
    };

    hand.Initialise();
}

void ForeArm::ShutDown()
{

}

void ForeArm::Update(float dt)
{
    (void)dt;
}

void ForeArm::Draw()
{
    DrawModelEx(
        assets.foreArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelWiresEx(
        assets.foreArm,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        GREEN
    );

    hand.Draw();
}

void ForeArm::SetTransform(MyTransform3D parentTransform)
{
    transform = parentTransform;
    transform.position = Vector3Add(parentTransform.position, positionOffset);
    hand.SetTransform(transform);
}
