#include "SceneManager.h"

int SceneManager::sceneCounter = 0;

// Singleton design pattern, we only need one scene manager within this game;
SceneManager& SceneManager::getInstance()
{
    static SceneManager instance;
    return instance;
}


SceneManager& SceneManager::AddScene(std::unique_ptr<Scene> scene)
{
    if (scene != nullptr)
    {
        sceneCounter++;
        sceneMap[sceneCounter] = std::move(scene);
        std::cout << "Scene added" << std::endl;
    }

    return *this;
}

void SceneManager::SetScene(int number)
{
    std::cout << "Begin of set scene" << std::endl;
    auto it = sceneMap.find(number);
    if (it != sceneMap.end())
    {
        std::cout << "Checking..." << std::endl;
        currentScene = it->second.get();
    }
    else
    {
        std::cout << "Scene " << number << " not found!" << std::endl;
        currentScene = nullptr;
    }
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
    std::cout << "Our scene is: " << currentScene << std::endl;
    if (currentScene != nullptr)
    {
        std::cout << "In the update scene" << std::endl;
        currentScene->UpdateScene(player, camera);
    }
}

int SceneManager::GetSceneCount()
{
    return sceneCounter;
}

Scene* SceneManager::getCurrentScene()
{
    if (currentScene != nullptr)
    {
        std::cout << "We have a scene!" << std::endl;
        return currentScene;
    }
    else
    {
        return nullptr;
    }
}
