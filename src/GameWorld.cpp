#include "GameWorld.h"
#include <cmath>
#include "raymath.h"
#include "TingoBingo/TingoDimensions.h"

static float LerpAngle(float current, float target, float amount)
{
    float difference = target - current;

    while (difference > 180.0f)
        difference -= 360.0f;

    while (difference < -180.0f)
        difference += 360.0f;

    return current + difference * amount;
}

GameWorld::GameWorld(InputController& inputController) :
    inputController(inputController),
    tingo(tingoAssets, dimensions),
    cube(gameAssets.cube, "object", true)
    
{}

void GameWorld::Initialise(ScreenDimensions& screenDimensions)
{
    spaceBackground = LoadTexture("assets/images/background/space.jpg");

    this->screenDimensions = screenDimensions;

    // Configure the 3D camera.
    camera.position = { -6.0, 10.0f, 15.0f };  // Move camera further away and higher // Camera's position in the 3D world (X, Y, Z)
    camera.target = { 0.0f, 5.0f, 0.0f };  // Point the camera looks at
    camera.up = { 0.0f, 1.0f, 0.0f };      // Defines the upward direction (positive Y)
    camera.fovy = 45.0f;                   // Vertical field of view in degrees
    camera.projection = CAMERA_PERSPECTIVE;// Objects farther away appear smaller

    tingoAssets.Initialise();
    
    dimensions.Initialise
    (
        tingoAssets.GetBodyDimensions(),
        tingoAssets.GetPelvisDimensions(),
        tingoAssets.GetThighDimensions(),
        tingoAssets.GetKneeDimensions(),
        tingoAssets.GetShinDimensions(),
        tingoAssets.GetFootDimensions(),
        tingoAssets.GetNeckDimensions(),
        tingoAssets.GetShoulderDimensions(),
        tingoAssets.GetHeadDimensions(),
        tingoAssets.GetUpperArmDimensions(),
        tingoAssets.GetForeArmDimensions(),
        tingoAssets.GetElbowDimensions(),
        tingoAssets.GetHandDimensions(),
        tingoAssets.GetFingerDimensions(),
        tingoAssets.GetMouthDisplayDimensions(),
        tingoAssets.GetEyeDimesnsions(),
        tingoAssets.GetPupilDimensions(),
        tingoAssets.GetNoseDimensions(),
        tingoAssets.GetEyeBrowDimensions(),
        tingoAssets.GetEarDimensions(),
        tingoAssets.GetAntennaDimensions(),
        tingoAssets.GetSpriteSheetDimensions()   
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

    gameAssets.Initialise();
   
    cube.Initialise();
   
    MyTransform3D initialObjectTransform;
   
    initialObjectTransform.position = {-6.0f, 8.0f, 2.0f};
    initialObjectTransform.rotationAngle = 0.0f;
    initialObjectTransform.rotationAxis = {0.0f, 1.0f, 0.0f};
    initialObjectTransform.scale = {1.0f, 1.0f, 1.0f};
    cube.SetTransform(initialObjectTransform);

    worldObjects.push_back(&cube);
}

void GameWorld::Update(float dt)
{
    HandleInput(dt);
    HandleController(dt);

    // Allow free movement around the 3D world.
    //UpdateCamera(&camera, CAMERA_FREE);

    tingoAssets.UpdateLighting(camera.position);
    gameAssets.UpdateLighting(camera.position);

    tingo.Update(dt, worldObjects);

    cube.Update(dt);
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

    //Floor.
    DrawPlane(
        { 0.0f, 0.0f, 0.0f },
        { 40, 40 },
        LIGHTGRAY
    );

    //DrawGrid(100, 1.0f);

    tingo.Draw();

    cube.Draw();

    EndMode3D();

    DrawOrientationGizmo();
    //DrawGesturesStates();

    DrawText(
        TextFormat("Visible objects: %i", 
            static_cast<int>(tingo.GetVisibleObjects().size())),
        100,
        100,
        20,
        GREEN
    );
}

void GameWorld::ShutDown()
{
    tingo.ShutDown();
    tingoAssets.ShutDown();
    gameAssets.ShutDown();
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
        case TingoState::BrainState::Greeting:
            stateName = "Greeting"; break;
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

void GameWorld::HandleInput(float dt)
{
    const float moveSpeed = 3.0f;

    Vector3 tingoDirection = { 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_O))    tingoDirection.z -= 1.0f;
    if (IsKeyDown(KEY_L))  tingoDirection.z += 1.0f;
    if (IsKeyDown(KEY_K))  tingoDirection.x -= 1.0f;
    if (IsKeyDown(KEY_SEMICOLON)) tingoDirection.x += 1.0f;
    if (IsKeyDown(KEY_R)) tingoDirection.y += 1.0f;
    if (IsKeyDown(KEY_F)) tingoDirection.y -= 1.0f;

    if (Vector3Length(tingoDirection) > 0.0f)
    {
        tingoDirection = Vector3Normalize(tingoDirection);

        tingo.GetTransform().position.x += tingoDirection.x * moveSpeed * dt;
        tingo.GetTransform().position.z += tingoDirection.z * moveSpeed * dt;
        tingo.GetTransform().position.y += tingoDirection.y * moveSpeed * dt;
    }

    tingo.SetTransform(tingo.GetTransform());

    Vector3 cubeDirection = { 0.0f, 0.0f, 0.0f };

    if (IsKeyDown(KEY_Y)) cubeDirection.z -= 1.0f;
    if (IsKeyDown(KEY_H)) cubeDirection.z += 1.0f;
    if (IsKeyDown(KEY_G)) cubeDirection.x -= 1.0f;
    if (IsKeyDown(KEY_J)) cubeDirection.x += 1.0f;
    if (IsKeyDown(KEY_Z)) cubeDirection.y += 1.0f;
    if (IsKeyDown(KEY_X)) cubeDirection.y -= 1.0f;

    if (Vector3Length(cubeDirection) > 0.0f)
    {
        cubeDirection = Vector3Normalize(cubeDirection);

        cube.GetTransform().position.x += cubeDirection.x * moveSpeed * dt;
        cube.GetTransform().position.z += cubeDirection.z * moveSpeed * dt;
        cube.GetTransform().position.y += cubeDirection.y * moveSpeed * dt;
    }

    cube.SetTransform(cube.GetTransform());
}

void GameWorld::HandleController(float dt)
{
    if (!inputController.IsConnected())
        return;

    const float moveSpeed = 3.0f;
    const float deadZone = 0.15f;
    const float rotationSpeed = 5.0f;

    float x = inputController.GetLeftStickX();
    float z = inputController.GetLeftStickY();

    if (fabsf(x) < deadZone) x = 0.0f;
    if (fabsf(z) < deadZone) z = 0.0f;

    Vector3 direction = { x, 0.0f, z };

    if (Vector3Length(direction) > 1.0f)
        direction = Vector3Normalize(direction);

    if (Vector3Length(direction) > 0.0f)
    {
        // Move Tingo.
        MyTransform3D& transform = tingo.GetTransform();

        transform.position.x += direction.x * moveSpeed * dt;
        transform.position.z += direction.z * moveSpeed * dt;

        // Calculate desired heading.
        float targetAngle = atan2f(direction.x, direction.z) * RAD2DEG;

        // Smoothly rotate.
        transform.rotationAxis = { 0.0f, 1.0f, 0.0f };

        transform.rotationAngle = LerpAngle(
            transform.rotationAngle,
            targetAngle,
            rotationSpeed * dt
        );

        tingo.SetTransform(transform);
    }
}