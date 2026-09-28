#pragma once

#include "BodyDimensions.h"
#include "Sprite.h"
#include "Shin.h"
class Knee : public Sprite
{
    public:
        public:
        explicit Knee(BodyDimensions& dimensions);
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const;
        void SetRotation(float rotation);
        void SetAnchorPoint(Vector2 anchorPoint);
        void Shutdown();

    private:
        BodyDimensions& dimensions;
        Vector2 localPositionOffset = {};

        Shin shin;
};