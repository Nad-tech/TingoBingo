#pragma once

#include "BodyDimensions.h"
#include "Shape.h"

class Foot : public Shape
{
    public:
        public:
        explicit Foot(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt);
        void Draw() const;
        void SetRotation(float rotation);
        void SetAnchorPoint(Vector2 anchorPoint);
        void Shutdown();

    private:
        BodyDimensions& dimensions;
        Vector2 localPositionOffset = {};
};