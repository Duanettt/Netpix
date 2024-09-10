#pragma once

#include <raylib.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Camera.h"

class SceneComponent
{
public:
    virtual void Update(CameraController& camera) = 0;
    virtual void Draw(CameraController& camera) = 0;
    virtual void Unload() = 0;
    virtual ~SceneComponent() {}  // Ensure proper cleanup of derived classes
};

class Background : public SceneComponent
{
public:
    Background(const char* filePath)
    {
        texture = LoadTexture(filePath);
        if (texture.width == 0 || texture.height == 0)
        {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
        }
    }

    void Update(CameraController& camera) override
    {

        // Loop the texture when it reaches the end

        if (camera.getCameraPosition().x <= -texture.width * 2)
        {
            std::cout << "We're in the if" << std::endl;
            xOffset = camera.getCameraOffset().x;
        }
        else
        {
            std::cout << "The position is: " << camera.getCameraPosition().x << "The texture width is: " << texture.width * 2 << std::endl;
            xOffset = 0;
        } 
    }

    void Draw(CameraController& camera) override
    {
        xOffset = camera.getCameraOffset().x; // Use only the horizontal offset
        DrawTextureEx(texture, Vector2{ -xOffset, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture, Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
    }

    void Unload() override
    {
        UnloadTexture(texture);
    }

    ~Background() override
    {
        Unload();
    }

private:
    Texture2D texture;
    float xOffset = 0.0f;
};

class Midground : public SceneComponent
{
public:
    Midground(const char* filePath)
    {
        texture = LoadTexture(filePath);
        if (texture.width == 0 || texture.height == 0)
        {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
        }
    }

void Update(CameraController& camera) override
{

    // Loop the texture when it reaches the end
    xOffset = camera.getCameraOffset().x;
    if (xOffset <= -texture.width * 2) xOffset = 0;
}

    void Draw(CameraController& camera) override
    {
        xOffset = camera.getCameraOffset().x; // Use only the horizontal offset
        DrawTextureEx(texture, Vector2{ -xOffset, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture, Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
    }

    void Unload() override
    {
        // No resources to unload for Midground
    }

    ~Midground() override
    {
        Unload();
    }

private:
    Texture2D texture;
    float xOffset = 0.0f;
};

class Foreground : public SceneComponent
{
public:
    Foreground(const char* filePath)
    {
        texture = LoadTexture(filePath);
        if (texture.width == 0 || texture.height == 0)
        {
            TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
        }
    }

    void Update(CameraController& camera) override
    {

        // Loop the texture when it reaches the end
        xOffset = camera.getCameraOffset().x;
        if (xOffset >= -texture.width * 2) xOffset = 0;
    }


    void Draw(CameraController& camera) override
    {
        xOffset = camera.getCameraOffset().x; // Use only the horizontal offset
        DrawTextureEx(texture, Vector2{ -xOffset, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture, Vector2{ -xOffset + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
    }

    void Unload() override
    {
        // No resources to unload for Foreground
    }

    ~Foreground() override
    {
        Unload();
    }

private:
    Texture2D texture;
    float xOffset = 0.0f;
};


class Scene
{
public:
    void AddComponentPointerToSceneVector(SceneComponent* component)
    {
        components.push_back(component);
    }

    void DrawScene(Player& player, CameraController& camera) const
    {
        camera.BeginCameraMode();
        for (const auto& component : components)
        {
            component->Draw(camera);
        }

        player.Draw();

        camera.EndCameraMode();
    }

    void UpdateScene(Player& player, CameraController& camera)
    {
        camera.UpdateCamera(player.GetPlayerPosition());

        for (const auto& component : components)
        {
            component->Update(camera);
        }

        player.Update();
    }

    void Unload()
    {
        for (auto& component : components)
        {
            component->Unload();
        }
        components.clear();
    }

private:
    std::vector<SceneComponent*> components;
};


class SceneBuilder
{
public:
    SceneBuilder& AddComponent(std::unique_ptr<SceneComponent> component)
    {
        sceneComponents.push_back(std::move(component));
        return *this;
    };

    Scene Build()
    {
        Scene scene;
        for (const auto& component : sceneComponents)
        {
            scene.AddComponentPointerToSceneVector(component.get());
        }
        return scene;
    }

    void Unload()
    {
        sceneComponents.clear();
    }

private:
    std::vector<std::unique_ptr<SceneComponent>> sceneComponents;
};