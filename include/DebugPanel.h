#pragma once

#include "raylib.h"

#include <string>
#include <vector>

// A world-space debug panel for Raylib 3D scenes.
//
// Usage:
//   DebugPanel::Instance().Initialise();
//   DebugPanel::Instance().SetPosition({0.0f, 4.0f, 0.0f});
//   DebugPanel::Instance().Print("Blinking", true);
//   DebugPanel::Instance().Print("Eye scale", 0.42f);
//   ...
//   DebugPanel::Instance().Draw3D(camera); // inside BeginMode3D()/EndMode3D()
//   DebugPanel::Instance().Shutdown();     // before closing the window
//
// The panel uses a RenderTexture2D to draw normal 2D text, then displays
// that texture on a camera-facing 3D quad. Print() updates an existing label
// rather than adding duplicate rows.

class DebugPanel
{
public:
    // Returns the one shared DebugPanel instance. Any class can use this
    // without receiving a DebugPanel reference through its constructor.
    static DebugPanel& Instance();

    ~DebugPanel();

    // This is a singleton: prevent accidental copies or extra instances.
    DebugPanel(const DebugPanel&) = delete;
    DebugPanel& operator=(const DebugPanel&) = delete;
    DebugPanel(DebugPanel&&) = delete;
    DebugPanel& operator=(DebugPanel&&) = delete;

    // Call after InitWindow(), before using Print() or Draw3D().
    void Initialise();
    void Shutdown();

    void SetPosition(Vector3 position);
    Vector3 GetPosition() const;

    void SetWorldSize(float width, float height);
    void SetTextStyle(int fontSize, int lineSpacing, Color textColour);

    void SetVisible(bool visible);
    bool IsVisible() const;

    // Set or update a row. Supported types: string, const char*, float,
    // double, int, unsigned int, bool, Vector2, and Vector3.
    void Print(const std::string& label, const std::string& value);
    void Print(const std::string& label, const char* value);
    void Print(const std::string& label, float value);
    void Print(const std::string& label, double value);
    void Print(const std::string& label, int value);
    void Print(const std::string& label, unsigned int value);
    void Print(const std::string& label, bool value);
    void Print(const std::string& label, Vector2 value);
    void Print(const std::string& label, Vector3 value);

    void Clear();

    // Call inside BeginMode3D(camera) / EndMode3D().
    void Draw3D(const Camera3D& camera);

private:
    DebugPanel() = default;

    struct Entry
    {
        std::string label;
        std::string value;
    };

    std::vector<Entry> entries;

    RenderTexture2D renderTexture{};
    bool initialised = false;
    bool visible = true;

    Vector3 position = { 0.0f, 3.0f, 0.0f };
    float worldWidth = 2.8f;
    float worldHeight = 1.6f;

    int textureWidth = 1024;
    int textureHeight = 512;
    int fontSize = 60;
    int lineSpacing = 36;
    int padding = 18;

    Color textColour = LIME;
    Color panelColour = { 12, 18, 24, 220 };
    Color borderColour = { 90, 180, 130, 255 };

    void SetValue(const std::string& label, const std::string& value);
    void RefreshTexture();
};
