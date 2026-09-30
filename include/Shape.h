#pragma once

#include "raylib.h"
#include "Constants.h"
#include "MyTransform.h"
#include "BodyDimensions.h"
#include <string>

class Shape
{
protected:
    MyTransform transform;
    
    float width = 0.0f;
    float height = 0.0f;

    float screenX;
    float screenY;
    
    Color color;

    std::string name;

    bool hasJoint = false;

public:
    explicit Shape(Color color = CARDBOARD_DARK) : color(color) {}
    virtual void Initialise() = 0;
    
    virtual void Draw() const;
    
    void SetScreenCoords();
    void SetShapeName(std::string name);
    void SetDimensions(float w, float h);

    void DebugDraw() const;
    
    virtual ~Shape() = default;
};