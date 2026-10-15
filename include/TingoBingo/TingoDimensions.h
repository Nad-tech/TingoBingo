#pragma once

#include "raylib.h"

class TingoDimensions 
{
public:
    void Initialise
    (
        Vector3 bodyDimensions,
        Vector3 pelvisDimensions,
        Vector3 thighDimensions,
        Vector3 kneeDimensions,
        Vector3 shinDimensions, 
        Vector3 footDimensions,
        Vector3 neckDimensions
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
};