#include "../Scene.h"

Foreground::Foreground(const char* filePath) : SceneComponent(filePath)
{
}

Foreground::Foreground(std::string textureKey) : SceneComponent(textureKey)
{
}

void Foreground::Update(CameraController& camera)
{
    xOffset = camera.getCameraOffset().x;
    if (xOffset >= -texture.width * 2) xOffset = 0;
}

void Foreground::Draw(CameraController& camera)
{
    xOffset = camera.getCameraOffset().x;
    DrawTextureEx(texture, Vector2{ -xOffset, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
    DrawTextureEx(texture, Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
}

void Foreground::Unload()
{
    // No resources to unload
}

Foreground::~Foreground()
{
    Unload();
}
