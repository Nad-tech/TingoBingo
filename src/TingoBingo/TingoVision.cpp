#include "TingoBingo/TingoVision.h"

#include "raymath.h"

#include <iostream>

void TingoVision::Initialise()
{
    visibleObjects.clear();

    visionRange = 15.0f;
    visionFOV = 90.0f;
}

void TingoVision::Update(
    Vector3 observerPosition,
    const std::vector<GameObject*>& objects
)
{
    this->observerPosition = observerPosition;

    visibleObjects.clear();

    for (GameObject* object : objects)
    {
        if (object == nullptr)
            continue;

        if (
            IsWithinRange(observerPosition, object->GetBoundingBox()) &&
            IsWithinFieldOfView(observerPosition, object->GetPosition())
        )
        {
            visibleObjects.push_back(object);
        }
    }
}

bool TingoVision::IsWithinRange(
    Vector3 observerPosition,
    BoundingBox bounds
) const
{
    // Find the closest point on the bounding box
    // to Tingo's position.

    Vector3 closestPoint =
    {
        Clamp(observerPosition.x, bounds.min.x, bounds.max.x),
        Clamp(observerPosition.y, bounds.min.y, bounds.max.y),
        Clamp(observerPosition.z, bounds.min.z, bounds.max.z)
    };

    float distance = Vector3Distance(
        observerPosition,
        closestPoint
    );

    return distance <= visionRange;
}

const std::vector<GameObject*>&
TingoVision::GetVisibleObjects() const
{
    return visibleObjects;
}

void TingoVision::Draw()
{
    DrawSphereWires(
        observerPosition,
        visionRange,
        12,
        12,
        GREEN
    );

    DrawVisionCone();
}

bool TingoVision::IsWithinFieldOfView(
    Vector3 observerPosition,
    Vector3 targetPosition
) const
{
    Vector3 directionToTarget = Vector3Normalize(
        Vector3Subtract(targetPosition, observerPosition)
    );

    float dot = Vector3DotProduct(
        forwardDirection,
        directionToTarget
    );

    float threshold = cosf((visionFOV / 2.0f) * DEG2RAD);

    return dot >= threshold;
}

void TingoVision::DrawVisionCone() const
{
    const float halfAngle = visionFOV / 2.0f;

    const float coneRadius =
        tanf(halfAngle * DEG2RAD) * visionRange;

    Vector3 endPosition = Vector3Add(
        observerPosition,
        Vector3Scale(forwardDirection, visionRange)
    );

    DrawCylinderEx(
        observerPosition,
        endPosition,
        0.0f,
        coneRadius,
        24,
        Fade(RED, 0.15f)
    );

    // Draw the cone's wireframe.
    const int segments = 24;

    Vector3 up = { 0.0f, 1.0f, 0.0f };

    // Create a direction perpendicular to forward.
    Vector3 right = Vector3Normalize(
        Vector3CrossProduct(up, forwardDirection)
    );

    // Recalculate up to ensure perpendicular axes.
    up = Vector3Normalize(
        Vector3CrossProduct(forwardDirection, right)
    );

    for (int i = 0; i < segments; i++)
    {
        float angle1 = (2.0f * PI * i) / segments;
        float angle2 = (2.0f * PI * (i + 1)) / segments;

        Vector3 point1 = Vector3Add(
            endPosition,
            Vector3Add(
                Vector3Scale(right, cosf(angle1) * coneRadius),
                Vector3Scale(up, sinf(angle1) * coneRadius)
            )
        );

        Vector3 point2 = Vector3Add(
            endPosition,
            Vector3Add(
                Vector3Scale(right, cosf(angle2) * coneRadius),
                Vector3Scale(up, sinf(angle2) * coneRadius)
            )
        );

        // Draw the outer circular boundary.
        DrawLine3D(point1, point2, RED);

        // Draw a line from Tingo to the boundary.
        if (i % 3 == 0)
        {
            DrawLine3D(observerPosition, point1, RED);
        }
    }
}