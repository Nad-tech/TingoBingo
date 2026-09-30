#pragma once

#include "raylib.h"
#include "Constants.h"
#include "MyTransform.h"
#include "BodyDimensions.h"
#include <string>
#include "Animation.h"

class Sprite
{
protected:
    MyTransform transform;

    Texture2D texture;
    Animation animation;
    
    float width;
    float height;

    float screenX;
    float screenY;

    std::string name;

public:
    virtual void Initialise() = 0;
    
    virtual void Update(float dt);
    virtual void Draw() const;
    
    void SetScreenCoords();
    void SetShapeName(std::string name);
    void SetDimensions(float w, float h);

    void DebugDraw() const;
    
    void Shutdown();
    virtual ~Sprite() = default;
};