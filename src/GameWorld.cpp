#include "GameWorld.h"
#include <cmath>
#include "raymath.h"

void GameWorld::Initialise()
{
    // Configure the 3D camera.
    camera.position = { 18.0f, 15.0f, 20.0f };  // Move camera further away and higher // Camera's position in the 3D world (X, Y, Z)
    camera.target = { 0.0f, 0.0f, 0.0f };  // Point the camera looks at
    camera.up = { 0.0f, 1.0f, 0.0f };      // Defines the upward direction (positive Y)
    camera.fovy = 45.0f;                   // Vertical field of view in degrees
    camera.projection = CAMERA_PERSPECTIVE;// Objects farther away appear smaller

    tingo.Initialise();
}

void GameWorld::Update(float dt)
{
    // Allow free movement around the 3D world.
    UpdateCamera(&camera, CAMERA_FREE);

    tingo.Update(dt);
}

// Draw a screen-space widget showing the camera's orientation.
static void DrawOrientationGizmo(const Camera3D& camera)
{
    const Vector2 centre = { 740.0f, 80.0f };
    const float axisLength = 35.0f;

    // Calculate the direction from the camera towards its target.
    Vector3 forward = Vector3Normalize(
        Vector3Subtract(camera.target, camera.position)
    );

    // Calculate the camera's right and up directions.
    Vector3 right = Vector3Normalize(
        Vector3CrossProduct(forward, camera.up)
    );

    Vector3 up = Vector3Normalize(
        Vector3CrossProduct(right, forward)
    );

    // World axes and their colours.
    const Vector3 axes[] = {
        { 1.0f, 0.0f, 0.0f },  // X
        { 0.0f, 1.0f, 0.0f },  // Y
        { 0.0f, 0.0f, 1.0f }   // Z
    };

    const Color colours[] = {
        RED,
        GREEN,
        BLUE
    };

    const char* labels[] = { "X", "Y", "Z" };

    // Draw each world axis from the widget's centre.
    for (int i = 0; i < 3; i++)
    {
        const Vector3& axis = axes[i];

        // Project the world axis onto the camera's screen directions.
        float screenX = Vector3DotProduct(axis, right);
        float screenY = -Vector3DotProduct(axis, up);

        Vector2 end = {
            centre.x + screenX * axisLength,
            centre.y + screenY * axisLength
        };

        DrawLineEx(centre, end, 3.0f, colours[i]);

        // Place the axis label just beyond the line's endpoint.
        Vector2 labelPosition = {
            end.x + screenX * 8.0f - 5.0f,
            end.y + screenY * 8.0f - 6.0f
        };

        DrawText(
            labels[i],
            static_cast<int>(labelPosition.x),
            static_cast<int>(labelPosition.y),
            14,
            colours[i]
        );
    }

    // Mark the widget's centre.
    DrawCircleV(centre, 3.0f, DARKGRAY);
}

void GameWorld::Draw()
{
    BeginMode3D(camera);

    // Room dimensions.
    const float roomWidth = 20.0f;
    const float roomHeight = 8.0f;
    const float roomDepth = 20.0f;

    // Half-dimensions make positioning the walls easier.
    const float halfWidth = roomWidth / 2.0f;
    const float halfDepth = roomDepth / 2.0f;

    // Floor.
    DrawPlane(
        { 0.0f, 0.0f, 0.0f },
        { roomWidth, roomDepth },
        LIGHTGRAY
    );

    // Back wall: positive Z.
    DrawCube(
        { 0.0f, roomHeight / 2.0f, halfDepth },
        roomWidth, roomHeight, 0.2f,
        GRAY
    );

    // Front wall: negative Z.
    DrawCube(
        { 0.0f, roomHeight / 2.0f, -halfDepth },
        roomWidth, roomHeight, 0.2f,
        GRAY
    );

    // Left wall: negative X.
    DrawCube(
        { -halfWidth, roomHeight / 2.0f, 0.0f },
        0.2f, roomHeight, roomDepth,
        DARKGRAY
    );

    // Right wall: positive X.
    DrawCube(
        { halfWidth, roomHeight / 2.0f, 0.0f },
        0.2f, roomHeight, roomDepth,
        DARKGRAY
    );

    DrawGrid(100, 1.0f);

    tingo.Draw();

    EndMode3D();

    DrawOrientationGizmo(camera);
}

void GameWorld::Shutdown()
{
    tingo.ShutDown();
}