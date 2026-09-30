#include "Body/BodyBase.h"

#include "Constants.h"
#include <iostream>

BodyBase::BodyBase(BodyDimensions& dimensions) :
    dimensions(dimensions)
{
}

// Load the body sprite and initialise its animation.
void BodyBase::Initialise()
{
    Sprite::texture = LoadTexture("assets/images/TingoBingo/body/bodyBase.png");

    dimensions.bodyWidth = texture.width;
    dimensions.bodyHeight = texture.height;

    drawGeometry.width = texture.width;
    drawGeometry.height = texture.height;

    const int COLUMNS = 1;
    const int ROWS = 1;
    const int TOTAL_FRAMES = COLUMNS * ROWS;
    const float FRAME_DURATION = 0.02f;

    Sprite::animation.Initialise
    (
        dimensions.bodyWidth,
        dimensions.bodyHeight,
        TOTAL_FRAMES,
        COLUMNS,
        FRAME_DURATION
    );

    positionOffset = { 0.0f, 0.0f };

    drawGeometry.origin = {
        drawGeometry.width / 2.0f,
        drawGeometry.height / 2.0f
    };

    Sprite::SetShapeName("bodyBase");
}

void BodyBase::SetTransform(MyTransform parentTransform)
{
    Sprite::transform = MakeChildTransform(parentTransform, positionOffset);
    
    Sprite::SetScreenCoords();
}