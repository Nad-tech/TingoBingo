#pragma once

#include "raylib.h"
#include "Constants.h"
#include "MyTransform.h"
#include "BodyDimensions.h"
#include <string>
#include "Animation.h"
#include "DrawGeometry.h"

class Sprite
{
protected:
    MyTransform transform;
    DrawGeometry drawGeometry;

    Texture2D texture;
    Animation animation;
    
    float screenX;
    float screenY;

    std::string name;

    void DebugDraw() const;

public:
    virtual void Initialise() = 0;
    
    virtual void Update(float dt);
    virtual void Draw() const;
    
    void SetScreenCoords();
    void SetShapeName(std::string name);
    
    void Shutdown();
    virtual ~Sprite() = default;
};