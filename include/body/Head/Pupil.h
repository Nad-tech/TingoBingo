#pragma once

#include "Sprite.h"
#include <string>
#include "BodyDimensions.h"
#include "MyTransform.h"
#include "RobotState.h"

class Pupil : public Sprite
{
    public:
        Pupil(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise() override;
        
        using Sprite::Update;
        void Update(float dt);
        
        void SetSide(std::string side);
        float GetSideOffset();
        
        void SetPosition(Vector2 position);
        
        void SetRotation(float rotation);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        std::string side; // "left" or "right"
        float sideOffset = 40;
};