#include "GameWorld.h"
#include <cmath>
#include "raymath.h"
#include "TingoBingo/TingoDimensions.h"

GameWorld::GameWorld() :
    tingo(assets, dimensions)
{}

inline bool dirFlag = true;

void GameWorld::Initialise(ScreenDimensions& screenDimensions)
{
    DebugPanel::Instance().Initialise();
    DebugPanel::Instance().SetPosition({ -5.0f, 3.0f, 0.0f });
    DebugPanel::Instance().SetWorldSize(4.0f, 4.0f);
    DebugPanel::Instance().SetVisible(true);

    spaceBackground = LoadTexture("assets/images/background/space.jpg");

    this->screenDimensions = screenDimensions;

    // Configure the 3D camera.
    camera.position = { -6.0, 10.0f, 15.0f };  // Move camera further away and higher // Camera's position in the 3D world (X, Y, Z)
    camera.target = { 0.0f, 5.0f, 0.0f };  // Point the camera looks at
    camera.up = { 0.0f, 1.0f, 0.0f };      // Defines the upward direction (positive Y)
    camera.fovy = 45.0f;                   // Vertical field of view in degrees
    camera.projection = CAMERA_PERSPECTIVE;// Objects farther away appear smaller

    assets.Initialise();
    dimensions.Initialise
    (
        assets.GetBodyDimensions(),
        assets.GetPelvisDimensions(),
        assets.GetThighDimensions(),
        assets.GetKneeDimensions(),
        assets.GetShinDimensions(),
        assets.GetFootDimensions(),
        assets.GetNeckDimensions(),
        assets.GetShoulderDimensions(),
        assets.GetHeadDimensions(),
        assets.GetUpperArmDimensions(),
        assets.GetForeArmDimensions(),
        assets.GetElbowDimensions(),
        assets.GetHandDimensions(),
        assets.GetFingerDimensions(),
        assets.GetMouthDisplayDimensions(),
        assets.GetEyeDimesnsions(),
        assets.GetPupilDimensions(),
        assets.GetNoseDimensions(),
        assets.GetEyeBrowDimensions(),
        assets.GetEarDimensions(),
        assets.GetAntennaDimensions(),
        assets.GetSpriteSheetDimensions()   
    );

    initialTransform.position = {
        0.0f, 
        dimensions.bodyShape.height / 2.0f +
        dimensions.pelvis.height +
        dimensions.thigh.height +
        dimensions.knee.height +
        dimensions.shin.height +
        dimensions.foot.height, 
        0.0f
    };

    initialTransform.rotationAxis = {1.0f, 1.0f, 1.0f};
    initialTransform.rotationAngle = 0.0f;
    initialTransform.scale = dimensions.globalScale;

    tingo.Initialise();
    tingo.SetTransform(initialTransform);
}

void GameWorld::Update(float dt)
{
    // Allow free movement around the 3D world.
    UpdateCamera(&camera, CAMERA_FREE);

    assets.UpdateLighting(camera.position);

    // dirFlag ? initialTransform.rotationAngle += dt * 80 : initialTransform.rotationAngle -= dt * 80;
     
    // if(initialTransform.rotationAngle <= 0.0) dirFlag = true;
    // if(initialTransform.rotationAngle >= 720.0) dirFlag = false;    

    tingo.SetTransform(initialTransform);
    tingo.Update(dt);
}

// Draw a screen-space widget showing the camera's orientation.
void GameWorld::DrawOrientationGizmo()
{
    float x = screenDimensions.screenWidth;

    const Vector2 centre = {
    static_cast<float>(x - 100),
    100.0f
};
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
    DrawTexturePro(
        spaceBackground,
        { 0.0f, 0.0f,
        (float)spaceBackground.width,
        (float)spaceBackground.height },
        { 0.0f, 0.0f,
        (float)GetScreenWidth(),
        (float)GetScreenHeight() },
        { 0.0f, 0.0f },
        0.0f,
        WHITE
    );

    BeginMode3D(camera);

    // Room dimensions.
    const float roomWidth = 20.0f;
    const float roomHeight = 8.0f;
    const float roomDepth = 20.0f;

    // Half-dimensions make positioning the walls easier.
    const float halfWidth = roomWidth / 2.0f;
    const float halfDepth = roomDepth / 2.0f;

    //Floor.
    DrawPlane(
        { 0.0f, 0.0f, 0.0f },
        { roomWidth, roomDepth },
        LIGHTGRAY
    );

    // // Front wall: positive Z.
    // /*DrawCube(
    //     { 0.0f, roomHeight / 2.0f, halfDepth },
    //     roomWidth, roomHeight, 0.2f,
    //     GRAY
    // );*/

    // Back wall wall: negative Z.
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

    //DebugPanel::Instance().Draw3D(camera);

    EndMode3D();

    DrawOrientationGizmo();
    DrawGesturesStates();
}

void GameWorld::Shutdown()
{
    tingo.ShutDown();
    DebugPanel::Instance().Shutdown();
}
void GameWorld::DrawGesturesStates()
{
    int x = 12;
    int y = 12;
    const int fontSize = 20;
    const int lineHeight = fontSize + 4;
    //const int coloumnWidth = 200;
    
    const char* stateName = "Unknown";
    switch (tingo.GetState().brainState)
    {
        case TingoState::BrainState::Idle: 
            stateName = "Idle"; break;
        case TingoState::BrainState::Sleeping: 
            stateName = "Sleeping"; break;
    }

    DrawText("TINGO STATE", x, y, 16, YELLOW);

    y += lineHeight;

    DrawText(
        TextFormat
        (
            "State: %s", stateName
        ), 
        x, 
        y, 
        fontSize, 
        RAYWHITE
    );
    
    const char* waveStateName = "Unknown";
    switch (tingo.GetState().waveState)
    {
        case TingoState::WaveState::Inactive: 
            waveStateName = "Inactive"; break;
        case TingoState::WaveState::WaveLeft: 
            waveStateName = "Wave left"; break;
        case TingoState::WaveState::WaveRight: 
            waveStateName = "Wave right"; break;
    }

    y += lineHeight;
    DrawText("TINGO WAVE STATE", x, y, 16, YELLOW);

    y += lineHeight;

    DrawText(
        TextFormat
        (
            "Wave State: %s", waveStateName
        ), 
        x, 
        y, 
        fontSize, 
        RAYWHITE
    );
}

