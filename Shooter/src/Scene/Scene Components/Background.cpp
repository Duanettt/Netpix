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
    float texWidth = texture.width;

    // Ensure continuous scrolling
    if (camera.getCameraPosition().x <= -texWidth || camera.getCameraPosition().x >= texWidth)
    {
        xOffset = fmod(camera.getCameraOffset().x, texWidth);
    }
    else
    {
        xOffset = camera.getCameraOffset().x;
    }
}
void Background::Draw(CameraController& camera)
{
    // Get the camera offset
    xOffset = camera.getCameraOffset().x;
    // Apply it to the two adjacent background textures for a little parallax effect.
    Vector2 vectorBg1Pos = Vector2{ -xOffset, 450.0f - (texture.height * 2) };
    Vector2 vectorBg2Pos = Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) };

    DrawTextureEx(texture, vectorBg1Pos, 0.0f, 2.0f, WHITE);
    DrawTextureEx(texture, vectorBg2Pos, 0.0f, 2.0f, WHITE);
}

void Background::Unload()
{
    UnloadTexture(texture);
}

Background::~Background()
{
    Unload();
}
