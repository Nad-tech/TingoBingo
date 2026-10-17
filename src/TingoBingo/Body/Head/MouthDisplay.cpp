#include "TingoBingo/Body/Head/MouthDisplay.h"
#include "raymath.h"

MouthDisplay::MouthDisplay(TingoAssets& assets, TingoDimensions& dimensions) :
    assets(assets),
    dimensions(dimensions)
{}

void MouthDisplay::Initialise()
{
    float Yoffset = -dimensions.mouthDisplay.height / 2.0f - 
                    0.2f + dimensions.head.height / 2.0f;

    positionOffset = {
        0.0f,
        Yoffset,
        dimensions.head.length / 2.0f + dimensions.mouthDisplay.length / 2.0f        
    };

    mouthPlaneOffset = {0.0f, 0.0f, 0.06f};

    int frameWidth = 
        dimensions.mouthSpriteSheet.width / 
        dimensions.mouthSpriteSheet.cols;

    int frameHeight = 
        dimensions.mouthSpriteSheet.height /
        dimensions.mouthSpriteSheet.rows;
    
    int totalFrames = 
        dimensions.mouthSpriteSheet.rows *
        dimensions.mouthSpriteSheet.cols;
    
    float frameDuration = 0.1f;

        animation.Initialise
    (
        frameWidth, 
        frameHeight, 
        totalFrames, 
        dimensions.mouthSpriteSheet.cols, 
        frameDuration
    );

    // Generate a flat rectangular mesh for the mouth using 
    //the specified width and height.
    //The final two arguments (1, 1) specify one subdivision 
    //along the length and width.
    // LoadModelFromMesh() converts the generated mesh 
    //into a Model that Raylib can render.
    // The resulting model is stored in mouthPlane for
    //later positioning, texturing, and drawing.
    mouthPlane = LoadModelFromMesh(GenMeshPlane(
        dimensions.mouthDisplay.width,  // Width of the mouth plane
        dimensions.mouthDisplay.height, // Height of the mouth plane
        1,                               // Number of subdivisions along the width
        1                                // Number of subdivisions along the length
    ));

    // Assign the mouth sprite sheet image as the diffuse texture
    // for the first material on the mouth plane.
    // The diffuse texture determines the image displayed on the surface
    // of the 3D model, allowing us to display Tingo's mouth sprites.
    mouthPlane.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
        assets.mouthSpriteSheet;

    SetMouthFrame(0);
}

void MouthDisplay::Update(float dt)
{
    animation.Update(dt);
}

void MouthDisplay::Draw()
{
   // Rectangle source = animation.GetSourceRectangle();

    DrawModelEx(
        assets.mouthDisplay,
        transform.position,
        transform.rotationAxis,
        transform.rotationAngle,
        transform.scale,
        WHITE
    );

    DrawModelEx(
        mouthPlane,
        mouthPlaneTransform.position,
        mouthPlaneTransform.rotationAxis,
        mouthPlaneTransform.rotationAngle,
        mouthPlaneTransform.scale,
        WHITE
    );
}

void MouthDisplay::SetTransform(MyTransform3D parentTransform)
{
    MyTransform3D localTransform{};

    localTransform.position = positionOffset;
    localTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localTransform.rotationAngle = 0.0f;
    localTransform.scale = dimensions.scale;

    transform = MakeChildTransform(parentTransform, localTransform);

    MyTransform3D localMouthPlaneTransform{};

    localMouthPlaneTransform.position = mouthPlaneOffset;
    localMouthPlaneTransform.rotationAxis = {1.0f, 0.0f, 0.0f};
    localMouthPlaneTransform.rotationAngle = 90.0f;
    localMouthPlaneTransform.scale = dimensions.scale;

    mouthPlaneTransform = 
        MakeChildTransform(transform, localMouthPlaneTransform);
}

void MouthDisplay::SetMouthFrame(int frame)
{
    animation.SetFrame(frame);

    int col = frame % dimensions.mouthSpriteSheet.cols;
    int row = frame / dimensions.mouthSpriteSheet.cols;

    float frameWidth =
    1.0f / dimensions.mouthSpriteSheet.cols;

    float frameHeight =
        1.0f / dimensions.mouthSpriteSheet.rows;

    float u0 = col * frameWidth;
    float u1 = u0 + frameWidth;

    float v0 = row * frameHeight;
    float v1 = v0 + frameHeight;

    float* texcoords = mouthPlane.meshes[0].texcoords;

    texcoords[0] = u0;
    texcoords[1] = v0;

    texcoords[2] = u1;
    texcoords[3] = v0;

    texcoords[4] = u0;
    texcoords[5] = v1;

    texcoords[6] = u1;
    texcoords[7] = v1;

    // Update the GPU's texture-coordinate buffer for the mouth mesh.
    // mouthPlane.meshes[0] selects the first mesh in the mouth model.
    // 1 identifies the texture-coordinate (UV) buffer.
    // texcoords contains the updated UV coordinates.
    // 8 * sizeof(float) specifies the number of bytes to upload
    // (8 floats, representing UV coordinates for 4 vertices).
    // 0 specifies the starting offset in the buffer.
    UpdateMeshBuffer(
        mouthPlane.meshes[0],
        1,
        texcoords,
        8 * sizeof(float),
        0
    );
}

void MouthDisplay::ShutDown()
{
    UnloadModel(mouthPlane);
}