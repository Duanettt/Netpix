#include "../Scene.h"


// Each scene component e.g Background we load our texture into the object. (Will change once we create our resource manager)
// FIXME: We're reusing code a bunch with the same constructor and we can use inheritance to solve this.. can do this at a later point. (FIXED)
Background::Background(const char* filePath) : SceneComponent(filePath)
{
}

Background::Background(std::string textureKey) : SceneComponent(textureKey)
{
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
