#pragma once

#include <raylib.h>
#include <vector>
#include <memory>
#include "Player.h"

class SceneComponent
{
public:
    virtual void Update() = 0;
    virtual void Draw() const = 0;
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

    void Update() override
    {
        scrollingBack -= 0.1f;

        if (scrollingBack <= -texture.width * 2) scrollingBack = 0;
    }

    void Draw() const override
    {
        DrawTextureEx(texture, Vector2{ scrollingBack, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture, Vector2{ scrollingBack + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
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
    float scrollingBack = 0.0f;
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

    void Update() override
    {
        scrollingBack -= 0.5f;

        if (scrollingBack <= -texture.width * 2) scrollingBack = 0;
    }

    void Draw() const override
    {
        DrawTextureEx(texture, Vector2{ scrollingBack, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture, Vector2{ scrollingBack + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
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
    float scrollingBack = 0.0f;
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

    void Update() override
    {
        scrollingBack -= 1.0f;

        if (scrollingBack <= -texture.width * 2) scrollingBack = 0;
    }

    void Draw() const override
    {
        DrawTextureEx(texture, Vector2{ scrollingBack, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(texture, Vector2{ scrollingBack + texture.width * 2, 450.0f - (texture.height * 2) }, 0.0f, 2.0f, WHITE);
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
    float scrollingBack = 0.0f;
};


class Scene
{
public:
    void AddComponentPointerToSceneVector(SceneComponent* component)
    {
        components.push_back(component);
    }

    void DrawScene(Player& player) const
    {
        for (const auto& component : components)
        {
            component->Draw();
        }

        player.Draw();
    }

    void UpdateScene(Player& player)
    {
        for (const auto& component : components)
        {
            component->Update();
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