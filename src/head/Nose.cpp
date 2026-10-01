#include "Body/Head/Nose.h"
#include "Constants.h"
#include <iostream>
#include <cmath>

Nose::Nose(BodyDimensions& dimensions) : dimensions(dimensions)
{}

void Nose::Initialise()
{
    Sprite::texture = LoadTexture("assets/images/TingoBingo/head/nose.png");

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.08f;

    dimensions.noseWidth = texture.width / COLUMNS;
    dimensions.noseHeight = texture.height / ROWS;

    Sprite::drawGeometry.width = dimensions.noseWidth;
    Sprite::drawGeometry.height = dimensions.noseHeight;
    
    animation.Initialise(
        dimensions.noseWidth,
        dimensions.noseHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = {
        0.0f,
        -slightPositionOffset
    };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };
}


void Nose::Update(float dt, Emotion emotion)
{
    Sprite::Update(dt);
}

void Nose::Draw() const
{
    Sprite::Draw();
}

void Nose::SetTransform(MyTransform parentTransform)
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    Sprite::SetScreenCoords();
}