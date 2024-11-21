#pragma once

#pragma once
#include <raylib.h>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include "../Game/Player.h"
#include "../Core/Camera.h"
#include "../Game/GameObjects.h"
#include "../Sound/Music.h"
#include "../ResourceManager.h"
#include "../DialogueManager.h"

class SceneComponent
{
public:
    SceneComponent(const char* filePath);
    SceneComponent(std::string textureKey);
    virtual void Update(CameraController& camera) = 0;
    virtual void Draw(CameraController& camera) = 0;
    virtual void Unload() = 0;
    Texture2D getTexture();
    virtual ~SceneComponent();

protected:
    Texture2D texture;
    // Dont initialize resource managers in objects makes huge problems..
    //ResourceManager& rm = ResourceManager::getInstance();
};


class Background : public SceneComponent
{
public:
    Background(const char* filePath);
    Background(std::string textureKey);
    void Update(CameraController& camera) override;
    void Draw(CameraController& camera) override;
    void Unload() override;
    ~Background() override;

private:
    float xOffset = 0.0f;
};

class Midground : public SceneComponent
{
public:
    Midground(const char* filePath);
    Midground(std::string textureKey);

    void Update(CameraController& camera) override;
    void Draw(CameraController& camera) override;
    void Unload() override;
    ~Midground() override;

private:
    float xOffset = 0.0f;
    bool wallDetection = false;
};

class Foreground : public SceneComponent
{
public:
    Foreground(const char* filePath);
    Foreground(std::string textureKey);

    void Update(CameraController& camera) override;
    void Draw(CameraController& camera) override;
    void Unload() override;
    ~Foreground() override;

private:
    float xOffset = 0.0f;
};

class Scene
{
public:

    // This will be implemented soon I guess.
    template<typename T>
    void addPointerToSceneVector(T* component);

    void AddComponentPointerToSceneVector(SceneComponent* component);
    void AddGameObjectPointerToSceneVector(GameObjects* object);
    void AddMusicPointerToMusicMap(std::string musicName, MusicComponent* music);
    NPC* getNPC();
    NPC* getNPCByIndex(int num);
    float getWorldWidth();
    float getWorldHeight();
    void DrawScene(Player& player, CameraController& camera);
    void UpdateScene(Player& player, CameraController& camera);
    void Unload();
    void setCurrentSong(std::string musicName);
    bool checkCollisions(Player& player);


private:
    std::vector<SceneComponent*> components;
    std::vector<GameObjects*> objects;
    std::unordered_map<std::string, MusicComponent*> musicMap;
    MusicComponent* currentMusic = nullptr;

    DialogueManager dm; 

    GameObjects* closestObject = nullptr;

    bool collisionDetected = false;
};

class SceneBuilder
{
public:
    SceneBuilder& AddComponent(std::unique_ptr<SceneComponent> component);
    SceneBuilder& AddObject(std::unique_ptr<GameObjects> object);
    SceneBuilder& AddMusic(const std::string name, std::unique_ptr<MusicComponent> musicObject);
    Scene Build();
    void Unload();

private:
    std::vector<std::unique_ptr<SceneComponent>> sceneComponents;
    std::vector<std::unique_ptr<GameObjects>> gameObjects;
    std::unordered_map<std::string, std::unique_ptr<MusicComponent>> musicMap;
};

