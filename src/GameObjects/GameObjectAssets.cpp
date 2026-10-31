#include "GameObjects/GameObjectAssets.h"
#include "raymath.h"

inline Vector3 GetDimensions(Model model)
{
    BoundingBox bounds = GetModelBoundingBox(model);
    Vector3 dimensions = Vector3Subtract(bounds.max, bounds.min);
    return dimensions;
}

void GameObjectAssets::Initialise()
{
    object = LoadModel("assets/models/gameobjects/object.glb");
    
    // Load the lighting shaders.
    lightingShader = LoadShader(
        "assets/shaders/lighting.vs",
        "assets/shaders/lighting.fs"
    );

    // Set the shader locations used by raylib.
    lightingShader.locs[SHADER_LOC_VECTOR_VIEW] =
        GetShaderLocation(lightingShader, "viewPos");

    // Set our custom uniform locations.
    lightDirectionLoc =
        GetShaderLocation(lightingShader, "lightDirection");

    ambientLoc =
        GetShaderLocation(lightingShader, "ambient");

    viewPositionLoc =
        GetShaderLocation(lightingShader, "viewPos");

    // Configure the directional light.
    //
    // The vector represents the direction in which light rays travel.
    // The shader reverses this direction when calculating illumination.
    float lightDirection[3] = {
        0.5f,
        -0.6f,
        -1.0f
    };

    SetShaderValue(
        lightingShader,
        lightDirectionLoc,
        lightDirection,
        SHADER_UNIFORM_VEC3
    );

    // Low-level ambient illumination keeps shadows readable.
    float ambient[3] = {
        0.40f,
        0.40f,
        0.40f
    };

    SetShaderValue(
        lightingShader,
        ambientLoc,
        ambient,
        SHADER_UNIFORM_VEC3
    );

        // Collect all the models that should use the lighting shader.
    Model* models[] = {
        &object
    };

    // Assign the shader to every material in every model.
    for (Model* model : models)
    {
        for (int i = 0; i < model->materialCount; i++)
        {
            model->materials[i].shader = lightingShader;
        }
    }
}

void GameObjectAssets::UpdateLighting(Vector3 cameraPosition)
{
    SetShaderValue(
        lightingShader,
        viewPositionLoc,
        &cameraPosition,
        SHADER_UNIFORM_VEC3
    );
}

Vector3 GameObjectAssets::GetObjectDimensions()
{
    return GetDimensions(object);
}


void GameObjectAssets::ShutDown()
{
    UnloadModel(object);
    
    UnloadShader(lightingShader);
}
