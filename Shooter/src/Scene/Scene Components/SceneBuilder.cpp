#include "../Scene.h"
#include <iostream>

// This class builds our scene out of various components.

SceneBuilder& SceneBuilder::AddComponent(std::unique_ptr<SceneComponent> component)
{

    // use move to transfer ownership of our scene component object to the scene components vector.
    sceneComponents.push_back(std::move(component));
    // We use *this to chain scene components together as seen in main.
    return *this;
}

SceneBuilder& SceneBuilder::AddObject(std::unique_ptr<GameObjects> object)
{
    gameObjects.push_back(std::move(object));
    return *this;
}

SceneBuilder& SceneBuilder::AddMusic(const std::string name, std::unique_ptr<MusicComponent> musicObject)
{
    musicMap[name] = std::move(musicObject);
    return *this;
}

Scene SceneBuilder::Build()
{
    Scene scene;

    // Create a scene varaible
    // Add every component to our scene vectors
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

    std::cout << "Scene successfully built..." << std::endl;

    //this->sceneComponents.clear();
    //this->gameObjects.clear();
    return scene;
}

void SceneBuilder::Unload()
{

    // Unload everything to free memory again.
    sceneComponents.clear();
    gameObjects.clear();
    musicMap.clear();
}
