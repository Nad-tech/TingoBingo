#include "TingoBingo/TingoDimensions.h"

void TingoDimensions::Initialise
(
    Vector3 bodyDimensions,
    Vector3 pelvisDimensions,
    Vector3 thighDimensions,
    Vector3 kneeDimensions,
    Vector3 shinDimensions,
    Vector3 footDimensions,
    Vector3 neckDimensions
)
{
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
}