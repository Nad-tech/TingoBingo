#pragma once

#include "raylib.h"

class TingoDimensions 
{
public:

    Vector3 scale;

    void Initialise
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
    );

    struct BodyShape {
        float width;
        float height;
        float length;
    };
    BodyShape bodyShape;

    struct Pelvis {
        float width;
        float height;
        float length;
    };
    Pelvis pelvis;

    struct Thigh {
        float width;
        float height;
        float length;
    };
    Thigh thigh;

    struct Knee {
        float width;
        float height;
        float length;
    };
    Knee knee;

    struct Shin {
        float width;
        float height;
        float length;
    };
    Shin shin;

    struct Foot {
        float width;
        float height;
        float length;
    };
    Foot foot;

    struct Neck {
        float width;
        float height;
        float length;
    };
    Neck neck;

    struct Shoulder {
        float width;
        float height;
        float length;
    };
    Shoulder shoulder;

    struct Head {
        float width;
        float height;
        float length;
    };
    Head head;

    struct UpperArm {
        float width;
        float height;
        float length;
    };
    UpperArm upperArm;

    struct ForeArm {
        float width;
        float height;
        float length;
    };
    ForeArm foreArm;

    struct Elbow {
        float width;
        float height;
        float length;
    };
    Elbow elbow;

    struct Hand {
        float width;
        float height;
        float length;
    };
    Hand hand;

    struct Finger {
        float width;
        float height;
        float length;
    };
    Finger finger;    
    
    struct MouthDisplay {
        float width;
        float height;
        float length;
    };
    MouthDisplay mouthDisplay;

    struct Eye {
        float width;
        float height;
        float length;
    };
    Eye eye;
};