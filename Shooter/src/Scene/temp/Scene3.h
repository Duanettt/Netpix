#pragma once
// std lib functions
#include <raylib.h>
#include <unordered_map>
#include <vector>
#include <memory>

// Relative Paths
#include "../Game/Player.h"
#include "../Core/Camera.h"
#include "../Game/GameObjects.h"
#include "../Sound/Music.h"

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
    // Unfinished might be a decent idea to reduce the amount of add vectors we have..
    template<typename T>
    void addPointerToSceneVector(T* component)
    {

    }

    // For these we could use a template method.
    void AddComponentPointerToSceneVector(SceneComponent* component)
    {
        components.push_back(component);
    }

    void AddGameObjectPointerToSceneVector(GameObjects* object)
    {
        objects.push_back(object);
    }

    void AddMusicPointerToMusicMap(std::string musicName, MusicComponent* music)
    {
        musicMap[musicName] = music;
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
        }
        return nullptr;
    }

    NPC* getNPCByIndex(int num)
    {
        std::vector<NPC*> npcVec;

        for (const auto& object : objects)
        {
            NPC* npc = dynamic_cast<NPC*>(object);
            if (npc != nullptr)
            {
                npcVec.push_back(npc);
            } 
        }
        return npcVec[num];
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
        currentMusic->PlayMusic();

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
        currentMusic->UpdateMusic();

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

        this->checkCollisions(player);
    }

    void Unload()
    {
        for (auto& component : components)
        {
            component->Unload();
        }

        // Need more unloading functions for musicMap and objects
        components.clear();
    }

    void setCurrentSong(std::string musicName)
    {
        auto it = musicMap.find(musicName);
        if (it != musicMap.end())
        {
            currentMusic = it->second;
            std::cout << it->first;
            currentMusic->PlayMusic();
        }
        else
        {
            TraceLog(LOG_ERROR, "Current song chosen is not compatible with this scene!");
        }
    }

    // This doesnt work.... 
    bool checkCollisions(Player& player)
    {
        Rectangle playerRect = player.GetPlayerBoundingRect();
        for (const auto& object : objects)
        {
            NPC* npc = dynamic_cast<NPC*>(object);
            if (npc != nullptr)
            {
                if (CheckCollisionRecs(npc->GetCurrentObjectBoundingRect(), playerRect))
                {
                    //std::cout << "Collision Detected" << std::endl;
                    DrawRectangle(player.GetPlayerPosition().x, player.GetPlayerPosition().y, playerRect.width, playerRect.height, RED);
                    return true;
                }
            }
        }
        return false;
    }

private:
    std::vector<SceneComponent*> components;
    std::vector<GameObjects*> objects;
    std::unordered_map<std::string, MusicComponent*> musicMap;
    MusicComponent* currentMusic = nullptr;

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

    SceneBuilder& AddMusic(const std::string name,std::unique_ptr<MusicComponent> musicObject)
    {
        musicMap[name] = std::move(musicObject);
        return *this;
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

        for (const auto& [name, music] : musicMap)
        {
            scene.AddMusicPointerToMusicMap(name, music.get());
        }

        std::cout << "Scene sucessfully built..." << std::endl;
        return scene;
    }


    void Unload()
    {
        sceneComponents.clear();
        gameObjects.clear();
        musicMap.clear();
    }

private:
    std::vector<std::unique_ptr<SceneComponent>> sceneComponents;
    std::vector<std::unique_ptr<GameObjects>> gameObjects;
    std::unordered_map<std::string, std::unique_ptr<MusicComponent>> musicMap;
};