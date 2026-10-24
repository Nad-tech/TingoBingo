#include "TingoBingo/Body/Head/Eye.h"

#include "raymath.h"
#include <iostream>

#include "DebugPanel.h"

Eye::Eye(
    TingoAssets& assets,
    TingoDimensions& dimensions,
    TingoState& state,
    std::string side
) :
    assets(assets),
    dimensions(dimensions),
    state(state),
    side(side),
    pupil(assets, dimensions)
{
}

void Eye::Initialise()
{
    float Xoffset = 0.5f;
    float Yoffset = 0.3f + dimensions.head.height / 2.0f;

    if (side == "left")
    {
        positionOffset = {
            Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f
                + dimensions.eye.length / 2.0f
        };
    }
    else if (side == "right")
    {
        positionOffset = {
            -Xoffset,
            Yoffset,
            dimensions.head.length / 2.0f
        };
    }

    localScale = {1.0f, 1.0f, 1.0f};

    eyeState = EyeState::Open;

    pupil.Initialise();
}

void Eye::Update(float dt)
{
    AdvanceBlink(dt);
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

void Eye::AdvanceBlink(float dt)
{
    const float speed = 10.0f;
    const float minScale = 0.1f;
    const float maxScale = 1.0f;

    if (state.eyeStateBrain == TingoState::EyeStateBrain::Close)
    {
        if (eyeState != EyeState::Closed)
        {
            eyeState = EyeState::Closing;

            localScale.y -= dt * speed;

            if (localScale.y <= minScale)
            {
                localScale.y = minScale;
                eyeState = EyeState::Closed;
            }
        }
    }
    else if (state.eyeStateBrain == TingoState::EyeStateBrain::Open)
    {
        if (state.blinkState == TingoState::BlinkState::Blinking)
        {
            switch (eyeState)
            {
                case EyeState::Open:
                    eyeState = EyeState::Closing;
                    break;

                case EyeState::Closing:
                    localScale.y -= dt * speed;

                    if (localScale.y <= minScale)
                    {
                        localScale.y = minScale;
                        eyeState = EyeState::Opening;
                    }
                    break;

                case EyeState::Closed:
                    eyeState = EyeState::Opening;
                    break;

                case EyeState::Opening:
                    localScale.y += dt * speed;

                    if (localScale.y >= maxScale)
                    {
                        localScale.y = maxScale;
                        eyeState = EyeState::Open;
                    }
                    break;
            }
        }
        else
        {
            if (eyeState == EyeState::Closed)
            {
                eyeState = EyeState::Opening;
            }

            if (eyeState == EyeState::Opening ||
                eyeState == EyeState::Closing)
            {
                localScale.y += dt * speed;

                if (localScale.y >= maxScale)
                {
                    localScale.y = maxScale;
                    eyeState = EyeState::Open;
                }
            }
        }
    }

    SetTransform(tempParentTransform);
}

EyeState Eye::GetEyeState() const
{
    return eyeState;
}