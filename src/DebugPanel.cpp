#include "DebugPanel.h"

#include <iomanip>
#include <sstream>

DebugPanel& DebugPanel::Instance()
{
    // Created on first use and shared by every caller.
    static DebugPanel instance;
    return instance;
}

DebugPanel::~DebugPanel()
{
    // Raylib resources should be released while the Raylib window/context
    // still exists. Prefer calling Shutdown() explicitly before CloseWindow().
    // The destructor is a convenience for normal object lifetime ordering.
    Shutdown();
}

void DebugPanel::Initialise()
{
    if (initialised || !IsWindowReady())
        return;

    renderTexture = LoadRenderTexture(textureWidth, textureHeight);
    initialised = renderTexture.id != 0 && renderTexture.texture.id != 0;

    if (initialised)
    {
        SetTextureFilter(renderTexture.texture, TEXTURE_FILTER_BILINEAR);
        RefreshTexture();
    }
    else
    {
        if (renderTexture.id != 0)
            UnloadRenderTexture(renderTexture);

        renderTexture = {};
        TraceLog(LOG_WARNING, "DebugPanel: render texture allocation failed");
    }
}

void DebugPanel::Shutdown()
{
    if (initialised)
    {
        UnloadRenderTexture(renderTexture);
        renderTexture = {};
        initialised = false;
    }
}

void DebugPanel::SetPosition(Vector3 newPosition)
{
    position = newPosition;
}

Vector3 DebugPanel::GetPosition() const
{
    return position;
}

void DebugPanel::SetWorldSize(float width, float height)
{
    worldWidth = width;
    worldHeight = height;
}

void DebugPanel::SetTextStyle(int newFontSize, int newLineSpacing, Color newTextColour)
{
    fontSize = newFontSize > 0 ? newFontSize : 1;
    lineSpacing = newLineSpacing > 0 ? newLineSpacing : 1;
    textColour = newTextColour;
    RefreshTexture();
}

void DebugPanel::SetVisible(bool newVisible)
{
    visible = newVisible;
}

bool DebugPanel::IsVisible() const
{
    return visible;
}

void DebugPanel::SetValue(const std::string& label, const std::string& value)
{
    for (Entry& entry : entries)
    {
        if (entry.label == label)
        {
            if (entry.value != value)
            {
                entry.value = value;
                RefreshTexture();
            }
            return;
        }
    }

    entries.push_back({ label, value });
    RefreshTexture();
}

void DebugPanel::Print(const std::string& label, const std::string& value)
{
    SetValue(label, value);
}

void DebugPanel::Print(const std::string& label, const char* value)
{
    SetValue(label, value ? value : "(null)");
}

void DebugPanel::Print(const std::string& label, float value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    SetValue(label, stream.str());
}

void DebugPanel::Print(const std::string& label, double value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << value;
    SetValue(label, stream.str());
}

void DebugPanel::Print(const std::string& label, int value)
{
    SetValue(label, std::to_string(value));
}

void DebugPanel::Print(const std::string& label, unsigned int value)
{
    SetValue(label, std::to_string(value));
}

void DebugPanel::Print(const std::string& label, bool value)
{
    SetValue(label, value ? "true" : "false");
}

void DebugPanel::Print(const std::string& label, Vector2 value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2)
           << "(" << value.x << ", " << value.y << ")";
    SetValue(label, stream.str());
}

void DebugPanel::Print(const std::string& label, Vector3 value)
{
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2)
           << "(" << value.x << ", " << value.y << ", " << value.z << ")";
    SetValue(label, stream.str());
}

void DebugPanel::Clear()
{
    entries.clear();
    RefreshTexture();
}

void DebugPanel::RefreshTexture()
{
    if (!initialised)
        return;

    BeginTextureMode(renderTexture);
    ClearBackground(panelColour);

    // Simple border around the panel.
    DrawRectangleLinesEx(
        { 1.0f, 1.0f, static_cast<float>(textureWidth - 2),
          static_cast<float>(textureHeight - 2) },
        3.0f,
        borderColour
    );

    int y = padding;
    const int availableBottom = textureHeight - padding;

    for (const Entry& entry : entries)
    {
        if (y + fontSize > availableBottom)
            break;

        const std::string output = entry.label + ": " + entry.value;

        DrawText(
            output.c_str(),
            padding,
            y,
            fontSize,
            textColour
        );

        y += lineSpacing;
    }

    EndTextureMode();
}

void DebugPanel::Draw3D(const Camera3D& camera)
{
    if (!visible || !initialised)
        return;

    // raylib's billboard path builds the camera-facing quad and manages its
    // texture and render state. A negative source height corrects the
    // vertical inversion of RenderTexture2D textures.
    DrawBillboardPro(
        camera,
        renderTexture.texture,
        { 0.0f, 0.0f, static_cast<float>(textureWidth), -static_cast<float>(textureHeight) },
        position,
        { 0.0f, 1.0f, 0.0f },
        { worldWidth, worldHeight },
        { worldWidth * 0.5f, worldHeight * 0.5f },
        0.0f,
        WHITE
    );
}
