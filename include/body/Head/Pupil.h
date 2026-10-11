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
        
        void SetTransform(MyTransform parentTransform);

        void LookAt(Vector2 point);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset = {0.0f, 0.0f};

        Vector2 lookOffset = {0.0f, 0.0f};

        MyTransform tempParentTransform;
};