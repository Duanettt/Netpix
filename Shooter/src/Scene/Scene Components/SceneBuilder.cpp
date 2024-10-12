#include "../Scene.h"
#include <iostream>

SceneBuilder& SceneBuilder::AddComponent(std::unique_ptr<SceneComponent> component)
{
    sceneComponents.push_back(std::move(component));
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
    return scene;
}

void SceneBuilder::Unload()
{
    sceneComponents.clear();
    gameObjects.clear();
    musicMap.clear();
}
