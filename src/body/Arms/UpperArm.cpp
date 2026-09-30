#include "Body/Arms/UpperArm.h"
#include "Constants.h"
#include <cmath>
#include <iostream>

// Construct the upper arm using the shared body dimensions
// and the side of the body that the arm belongs to.
UpperArm::UpperArm(BodyDimensions& dimensions, std::string side) :
    Shape(CARDBOARD_LIGHT),
    dimensions(dimensions),
    side(side),
    elbow(dimensions, side)
{
}

// Initialise the upper arm and its animation.
void UpperArm::Initialise()
{
    dimensions.upperArmWidth = 50.0f;
    dimensions.upperArmHeight = 120.0f;

    Shape::SetDimensions(dimensions.upperArmWidth, dimensions.upperArmHeight);

    positionOffset = {
        0, 
        0
    };

    globalPivot = {0, 0};

    joint = {0 , dimensions.upperArmHeight / 2.0f};

    Shape::hasJoint = true;

    elbow.Initialise();
}

// Update the upper arm and its child elbow.
void UpperArm::Update(float dt)
{
    elbow.Update(dt);
}


// Draw the upper arm.
void UpperArm::Draw() const
{
    Shape::Draw();
    elbow.Draw();
}


// Swing the upper arm between the supplied minimum
// and maximum angles.
void UpperArm::SwingArm(
    float dt,
    float swingMinAngle,
    float swingMaxAngle
)
{
    // Advance the animation timer.
    swingTime += dt * SWING_SPEED;

    // Keep the timer inside one complete sine-wave cycle.
    if (swingTime >= 2.0f * PI)
    {
        swingTime -= 2.0f * PI;
    }

    // sinf() produces a value between -1 and +1.
    //
    // Convert that into a value between 0 and 1.
    //
    // This gives us a percentage that represents where we are
    // between the minimum and maximum swing angles.
    float unitAngle = 0;

    // The left arm uses the normal direction of the sine wave.
    if(side == "left")
    {
        unitAngle = (sinf(swingTime) + 1.0f) / 2.0f;
    }

    // The right arm swings in the opposite direction.
    if(side == "right")
    {
        unitAngle = -(sinf(swingTime) + 1.0f) / 2.0f;
    }

    // Convert the 0-to-1 value into the requested angle range.
    //
    // For example:
    //
    //     unitAngle = 0   -> swingMinAngle
    //     unitAngle = 0.5 -> halfway between the two
    //     unitAngle = 1   -> swingMaxAngle
    //
    // The result becomes the arm's local rotation.
    localRotation =
        swingMinAngle +
        unitAngle * (swingMaxAngle - swingMinAngle);
}


void UpperArm::SetTransform(MyTransform parentTransform)
{
    Shape::transform = MakeChildTransform(parentTransform, positionOffset);
    Shape::transform.rotation += localRotation;
    Shape::transform.globalPivot = globalPivot;
    Shape::transform.joint = joint;

    Shape::SetScreenCoords();

    elbow.SetTransform(Shape::transform);
}