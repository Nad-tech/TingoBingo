#pragma once
#include "BodyDimensions.h"
#include "Shape.h"
#include "Foot.h"
#include "RobotState.h"
#include <string>

class Shin : public Shape
{
    public:
        public:
        Shin(BodyDimensions& dimensions, std::string side, RobotState& robotState);
        
        void Initialise() override;
        
        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTrnsform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;
        Vector2 positionOffset;

        std::string side;

        Foot foot;
};