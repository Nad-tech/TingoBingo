#pragma once

#include "raylib.h"
#include "Constants.h"
#include "MyTransform.h"
#include "BodyDimensions.h"
#include <string>
#include "DrawGeometry.h"

class Shape
{
protected:
    MyTransform transform;
    DrawGeometry drawGeometry;
    
    float screenX;
    float screenY;
    
    Color color;

    std::string name;
    
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