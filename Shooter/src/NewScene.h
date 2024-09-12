#pragma once

#include <raylib.h>
#include <vector>
#include <memory>
#include "Player.h"
#include "Camera.h"
#include "GameObjects.h"

class SceneComponent
{
public:
    virtual void Update(CameraController& camera) = 0;
    virtual void Draw(CameraController& camera) = 0;
    virtual void Unload() = 0;

    Texture2D getTexture()
    {
        return texture;
    }

    virtual ~SceneComponent() {}  // Ensure proper cleanup of derived classes

protected:
    Texture2D texture;
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
            
            xOffset = camera.getCameraOffset().x;
        }
        else
        {
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


     

    }

    void Draw(CameraController& camera) override
    {
        // Use only the horizontal offset
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
    float xOffset = 0.0f;
    bool wallDetection = false;
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
    float xOffset = 0.0f;
};


class Scene
{
public:
    void AddComponentPointerToSceneVector(SceneComponent* component)
    {
        components.push_back(component);
    }

    void AddGameObjectPointerToSceneVector(GameObjects* object)
    {
        objects.push_back(object);
    }

    NPC* getNPC()
    {
        for (const auto& object : objects)
        {
            NPC* npc = dynamic_cast<NPC*>(object);
            if (npc != nullptr)
            {
                return npc;
            }
            return nullptr;
        }
    }

    float getWorldWidth()
    {
        for (const auto& component : components)
        {
            Foreground* fg = dynamic_cast<Foreground*>(component);
            if (fg != nullptr)
            {
               return fg->getTexture().width * 2;
            }
        }
        return 0.0f;
    }

    float getWorldHeight()
    {
        for (const auto& component : components)
        {
            Foreground* fg = dynamic_cast<Foreground*>(component);
            if (fg != nullptr)
            {
                return fg->getTexture().height * 2;
            }
        }
        return 0.0f;
    }

    void DrawScene(Player& player, CameraController& camera) const
    {
        camera.BeginCameraMode();

        for (const auto& component : components)
        {
            component->Draw(camera);
        }

        for (const auto& object : objects)
        {
            object->DrawObject(camera);
        }
        player.Draw();

        camera.EndCameraMode();
    }

    void UpdateScene(Player& player, CameraController& camera)
    {
        camera.UpdateCamera(player.GetPlayerPosition(), this->getWorldWidth(), this->getWorldHeight());

        for (const auto& component : components)
        {
            component->Update(camera);
        }

        for (const auto& object : objects)
        {
            object->UpdateObject();
        }

        player.Update(this->getWorldWidth());
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
    std::vector<GameObjects*> objects;

};


class SceneBuilder
{
public:
    SceneBuilder& AddComponent(std::unique_ptr<SceneComponent> component)
    {
        sceneComponents.push_back(std::move(component));
        return *this;
    };

    SceneBuilder& AddObject(std::unique_ptr<GameObjects> object)
    {
        gameObjects.push_back(std::move(object));
        return *this;
    }

    SceneBuilder& AddMusic(std::unique_ptr<Music> music)
    {

    }

    Scene Build()
    {
        Scene scene;

        for (const auto& component : sceneComponents)
        {
            scene.AddComponentPointerToSceneVector(component.get());
        }

        for (const auto& object : gameObjects)
        {

            scene.AddGameObjectPointerToSceneVector(object.get());
        }

        
        return scene;
    }

    void Unload()
    {
        sceneComponents.clear();
        gameObjects.clear();
    }

private:
    std::vector<std::unique_ptr<SceneComponent>> sceneComponents;
    std::vector<std::unique_ptr<GameObjects>> gameObjects;
    std::vector <std::unique_ptr<Music>> musicVec;
};