#include "TingoBingo/Body/Head/Eye.h"
#include "raymath.h"
#include <iostream>
#include "DebugPanel.h"

Eye::Eye(TingoAssets& assets, TingoDimensions& dimensions, std::string side) :
    assets(assets),
    dimensions(dimensions),
    side(side),
    pupil(assets, dimensions)
{}

void Eye::Initialise()
{
    float Xoffset = 0.5f;
    float Yoffset = 0.3f + dimensions.head.height / 2.0f;

    if(side == "left")
    {
        positionOffset = {
            Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f + dimensions.eye.length / 2.0f        
        };
    }
    else if(side == "right")
    {
        positionOffset = {
            -Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f        
        };
    }

    localScale = {1.0f, 1.0f, 1.0f};
    blinkSpeed = 10.0f;
    blinkState = BlinkState::None;

    pupil.Initialise();
}

void Eye::Update(float dt)
{
    AdvanceBlink(dt);

    std::string state = "NULL";
}

void Eye::Draw()
{
    DrawModelEx(
        assets.eye,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    pupil.Draw();
}

void Eye::SetTransform(MyTransform3D parentTransform)
{
    tempParentTransform = parentTransform;

    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = localScale;

    transform = MakeChildTransform(parentTransform, localTransform);

    pupil.SetTransform(transform);
}

void Eye::Blink()
{
    if (blinkState == BlinkState::None)
    {
        blinkState = BlinkState::Closing;
    }
}

void Eye::AdvanceBlink(float dt)
{
    switch (blinkState)
    {
        case BlinkState::Closing:

            localScale.y -= blinkSpeed * dt;

            if (localScale.y <= 0.0f)
            {
                localScale.y = 0.0f;
                blinkState = BlinkState::Opening;
            }

            break;

        case BlinkState::Opening:

            localScale.y += blinkSpeed * dt;

            if (localScale.y >= 1.0f)
            {
                localScale.y = 1.0f;
                blinkState = BlinkState::None;
            }

            break;

        case BlinkState::None:
            break;
    }

    SetTransform(tempParentTransform);
}