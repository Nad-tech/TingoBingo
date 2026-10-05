#pragma once

#include "Sprite.h"
#include "BodyDimensions.h"
#include "Pupil.h"
#include "RobotState.h"

class Eye : public Sprite
{
    public:
        Eye(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        
        void Initialise() override;
        void ShutDown();

        using Sprite::Update;
        void Update(float dt);
        void Draw() const;

        void SetTransform(MyTransform parentTransform);

        void Blink();
        void Close();
        void Open();

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
        std::string side;
        
        Pupil pupil;
}; 
