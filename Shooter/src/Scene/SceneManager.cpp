#include "SceneManager.h"

int SceneManager::sceneCounter = 0;

// Singleton design pattern, we only need one scene manager within this game;
SceneManager& SceneManager::getInstance()
{
    // Singleton since we do not need more than one scene manager ever within the program
    static SceneManager instance;
    return instance;
}


SceneManager& SceneManager::AddScene(std::unique_ptr<Scene> scene)
{
    // Check for if scene is a null pointer to prevent crashes.
    if (scene != nullptr)
    {
        // Increase the scene counter and add it to our hashmap.
        sceneCounter++;
        sceneMap[sceneCounter] = std::move(scene);
        std::cout << "Scene added" << std::endl;
    }
    // Allows for chaining of scene additions
    return *this;
}

void SceneManager::SetScene(int number)
{
    std::cout << "Begin of set scene" << std::endl;
    // Setting our scene based on our hashmap. Iterates over our hash map containning scenes to locate the scene we've set.
    auto it = sceneMap.find(number);
    if (it != sceneMap.end())
    {
        std::cout << "Checking..." << std::endl;
        // Sets our current scene to the value within our hashmap.
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
    //std::cout << "Our scene is: " << currentScene << std::endl;
    if (currentScene != nullptr)
    {
        //std::cout << "In the update scene" << std::endl;
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
        //std::cout << "We have a scene!" << std::endl;
        return currentScene;
    }
    else
    {
        return nullptr;
    }
}
