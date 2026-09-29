#pragma once
#include "BodyDimensions.h"
#include "Shape.h"
#include "Foot.h"

class Shin : public Shape
{
    public:
        public:
        explicit Shin(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt);
        void Draw() const;
        void SetRotation(float rotation);
        void SetAnchorPoint(Vector2 anchorPoint);
        void Shutdown();

    private:
        BodyDimensions& dimensions;
        Vector2 localPositionOffset = {};

        Foot foot;
};