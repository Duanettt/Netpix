#include "SceneManager.h"

int SceneManager::sceneCounter = 1;

// Singleton design pattern, we only need one scene manager within this game;
SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}


SceneManager& SceneManager::AddScene(Scene* scene)
{
    if (scene != nullptr)
    {
        sceneMap[sceneCounter] = scene;
    }
    return *this;
}

void SceneManager::SetScene(int number)
{
    currentScene = sceneMap[number];
}

void SceneManager::DrawCurrentScene(Player& player, CameraController& camera)
{
    if (currentScene != nullptr)
    {
        currentScene->DrawScene(player, camera);
    }
}

void SceneManager::UpdateCurrentScene(Player& player, CameraController& camera)
{
    if (currentScene != nullptr)
    {
        currentScene->UpdateScene(player, camera);
    }
}

Scene* SceneManager::getCurrentScene()
{
    if (currentScene != nullptr)
    {
        return currentScene;
    }
    else
    {
        return nullptr;
    }
}
