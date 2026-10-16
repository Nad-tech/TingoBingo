#include "TingoBingo/TingoDimensions.h"

void TingoDimensions::Initialise
(
    Vector3 bodyDimensions,
    Vector3 pelvisDimensions,
    Vector3 thighDimensions,
    Vector3 kneeDimensions,
    Vector3 shinDimensions,
    Vector3 footDimensions,
    Vector3 neckDimensions,
    Vector3 shoulderDimensions,
    Vector3 headDimensions,
    Vector3 upperArmDimensions,
    Vector3 foreArmDimensions,
    Vector3 elbowDimensions,
    Vector3 handDimensions,
    Vector3 fingerDimensions,
    Vector3 mouthDisplayDimensions,
    Vector3 eyeDimensions
)
{
    scale = {1.0f, 1.0f, 1.0f};

    bodyShape.width = bodyDimensions.x;
    bodyShape.height = bodyDimensions.y;
    bodyShape.length = bodyDimensions.z;

    pelvis.width = pelvisDimensions.x;
    pelvis.height = pelvisDimensions.y;
    pelvis.length = pelvisDimensions.z;

    thigh.width = thighDimensions.x;
    thigh.height = thighDimensions.y;       
    thigh.length = thighDimensions.z;

    knee.width = kneeDimensions.x;
    knee.height = kneeDimensions.y;
    knee.length = kneeDimensions.z;

    shin.width = shinDimensions.x;
    shin.height = shinDimensions.y;
    shin.length = shinDimensions.z;

    foot.width = footDimensions.x;
    foot.height = footDimensions.y; 
    foot.length = footDimensions.z;

    neck.width = neckDimensions.x;
    neck.height = neckDimensions.y;
    neck.length = neckDimensions.z;

    shoulder.width = shoulderDimensions.x;
    shoulder.height = shoulderDimensions.y;
    shoulder.length = shoulderDimensions.z;

    head.width = headDimensions.x;
    head.height = headDimensions.y; 
    head.length = headDimensions.z;

    upperArm.width = upperArmDimensions.x;
    upperArm.height = upperArmDimensions.y;
    upperArm.length = upperArmDimensions.z;

    foreArm.width = foreArmDimensions.x;
    foreArm.height = foreArmDimensions.y;
    foreArm.length = foreArmDimensions.z;

    elbow.width = elbowDimensions.x;
    elbow.height = elbowDimensions.y;
    elbow.length = elbowDimensions.z;

    hand.width = handDimensions.x;
    hand.height = handDimensions.y;
    hand.length = handDimensions.z;

    finger.width = fingerDimensions.x;
    finger.height = fingerDimensions.y;
    finger.length = fingerDimensions.z;

    mouthDisplay.width = mouthDisplayDimensions.x;
    mouthDisplay.height = mouthDisplayDimensions.y;
    mouthDisplay.length = mouthDisplayDimensions.z;

    eye.width = eyeDimensions.x;
    eye.height = eyeDimensions.y;
    eye.length = eyeDimensions.z;
}