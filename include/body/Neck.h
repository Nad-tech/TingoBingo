#pragma once

#include "Body/Head/Head.h"
#include "Shape.h"
#include "BodyDimensions.h"
#include "MyTransform.h"
#include <string>
#include "RobotState.h"

class Neck : public Shape
{
    public:
        Neck(BodyDimensions& dimensions, RobotState& robotState);
        void Initialise() override;
        void Shutdown();
        
        void Update(float dt);
        void Draw() const override;
        
        void SetTransform(MyTransform parentTransform);
        
    private:
        BodyDimensions& dimensions;
        Vector2 positionOffset;
        RobotState& robotState;

        Head head;

        std::string name = "neck";
};