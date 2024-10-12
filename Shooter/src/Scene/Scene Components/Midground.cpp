#include "../Scene.h"

Midground::Midground(const char* filePath)
{
    texture = LoadTexture(filePath);
    if (texture.width == 0 || texture.height == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
    }
}

void Midground::Update(CameraController& camera)
{
    xOffset = camera.getCameraOffset().x;
}

void Midground::Draw(CameraController& camera)
{
    DrawTextureEx(texture, Vector2{ -xOffset, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(texture, Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
}

void Midground::Unload()
{
    // No resources to unload
}

Midground::~Midground()
{
    Unload();
}
