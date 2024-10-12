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

class SceneComponent
{
public:
    virtual void Update(CameraController& camera) = 0;
    virtual void Draw(CameraController& camera) = 0;
    virtual void Unload() = 0;
    Texture2D getTexture();
    virtual ~SceneComponent();

protected:
    Texture2D texture;
};

class Background : public SceneComponent
{
public:
    Background(const char* filePath);
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
    template<typename T>
    void addPointerToSceneVector(T* component);
    void AddComponentPointerToSceneVector(SceneComponent* component);
    void AddGameObjectPointerToSceneVector(GameObjects* object);
    void AddMusicPointerToMusicMap(std::string musicName, MusicComponent* music);
    NPC* getNPC();
    NPC* getNPCByIndex(int num);
    float getWorldWidth();
    float getWorldHeight();
    void DrawScene(Player& player, CameraController& camera) const;
    void UpdateScene(Player& player, CameraController& camera);
    void Unload();
    void setCurrentSong(std::string musicName);
    bool checkCollisions(Player& player);

private:
    std::vector<SceneComponent*> components;
    std::vector<GameObjects*> objects;
    std::unordered_map<std::string, MusicComponent*> musicMap;
    MusicComponent* currentMusic = nullptr;
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

