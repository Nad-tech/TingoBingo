#pragma once
#include "Body/Legs/Legs.h"
#include "Shape.h"
#include "BodyDimensions.h"
#include "RobotState.h"

class Pelvis : Shape
{
    public:
        Pelvis(BodyDimensions& dimensions, RobotState& robotState);
        void Initialise() override;
        void Shutdown();
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

        void Crouch();

    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;

        RobotState& robotState;
        
        Legs legs;
};
