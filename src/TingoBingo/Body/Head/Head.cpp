#include "TingoBingo/Body/Head/Head.h"
#include "raymath.h"

Head::Head(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions),
    mouthDisplay(assets, dimensions),
    leftEye(assets, dimensions, "left"),
    rightEye(assets, dimensions, "right"),
    nose(assets, dimensions),
    leftEyeBrow(assets, dimensions, "left"),
    rightEyeBrow(assets, dimensions, "right"),
    leftEar(assets, dimensions, "left"),
    rightEar(assets, dimensions, "right")
{}

void Head::Initialise()
{
    positionOffset = {
        0.0f,
        dimensions.neck.height / 2.0f,
        0.0f        
    };

    mouthDisplay.Initialise();
    leftEye.Initialise();
    rightEye.Initialise();
    nose.Initialise();
    leftEyeBrow.Initialise();
    rightEyeBrow.Initialise();
    leftEar.Initialise();
    rightEar.Initialise();
}

void Head::Update(float dt)
{
    (void)dt;

    //localRotation += dt * 50;
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

    mouthDisplay.Draw();
    leftEye.Draw();
    rightEye.Draw();
    nose.Draw();
    leftEyeBrow.Draw();
    rightEyeBrow.Draw();
    leftEar.Draw();
    rightEar.Draw();
}

void Head::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    localTransform.rotationAngle = localRotation;
    localTransform.scale = {1.0f, 1.0f, 1.0f};

    transform = MakeChildTransform(parentTransform, localTransform);

    mouthDisplay.SetTransform(transform);
    leftEye.SetTransform(transform);
    rightEye.SetTransform(transform);
    nose.SetTransform(transform);
    leftEyeBrow.SetTransform(transform);
    rightEyeBrow.SetTransform(transform);
    leftEar.SetTransform(transform);
    rightEar.SetTransform(transform);
}