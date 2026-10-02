#pragma once

class Robot;

class RobotBrain
{
    public:

        RobotBrain(Robot& robot);

        void Update(float dt);
        void Draw() const;
        
    private:
        Robot& robot;
        
};