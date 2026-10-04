#pragma once

#include "BodyDimensions.h"
#include "RobotState.h"
#include "EyeBrow.h"
#include "MyTransform.h"

class EyeBrows
{
    public:
        EyeBrows(BodyDimensions& dimensions, RobotState& robotState);
        
        void Initialise();
        void ShutDown();

        void Update(float dt);
        void Draw() const;
        
        void SetTransform(MyTransform parentTransform);

    private:
        BodyDimensions& dimensions;
        RobotState& robotState;

        EyeBrow leftEyeBrow;
        EyeBrow rightEyeBrow;
};