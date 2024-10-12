#include "../Scene.h"

Background::Background(const char* filePath)
{
    texture = LoadTexture(filePath);
    if (texture.width == 0 || texture.height == 0)
    {
        TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
    }
}

void Background::Update(CameraController& camera)
{
    if (camera.getCameraPosition().x <= -texture.width * 2)
    {
        xOffset = camera.getCameraOffset().x;
    }
    else
    {
        xOffset = 0;
    }
}

void Background::Draw(CameraController& camera)
{
    xOffset = camera.getCameraOffset().x;
    DrawTextureEx(texture, Vector2{ -xOffset, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(texture, Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
}

void Background::Unload()
{
    UnloadTexture(texture);
}

Background::~Background()
{
    Unload();
}
