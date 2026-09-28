#pragma once

#include "BodyDimensions.h"
#include "Sprite.h"
#include <string>

class Hand : public Sprite
{
    public:
        Hand(BodyDimensions& dimensions, std::string side);
        void Initialise() override;
        void Update(float dt) override;
        void Draw() const override;
        
        int GetFrame() const;
        
        void SetRotation(float rotation);
        
    private:
        BodyDimensions& dimensions;
        Vector2 localPositionOffset = {0, 0};
        float localRotation = 0.0f;
        float homeRotation = 0.0f;
        std::string side = "";
};