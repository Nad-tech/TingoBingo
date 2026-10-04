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
        
        void Update(float dt);
        void Draw() const;
        
        void SetPosition(Vector2 position);
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;
};