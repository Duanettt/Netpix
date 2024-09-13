#pragma once

#include "Scene.h"
#include "../Game/Player.h"
#include "../Core/Camera.h"
#include <unordered_map>


class SceneManager
{
public:
	static SceneManager& getInstance();

	// Adds scene to our map
	SceneManager& AddScene(Scene* scene);
	// Sets the scene
	void SetScene(int number);
	// Draws the current scene
	void DrawCurrentScene(Player& player, CameraController& camera);
	// Updates our current scene.
	void UpdateCurrentScene(Player& player, CameraController& camera);

	Scene* getCurrentScene();
private:
	static int sceneCounter;
	static SceneManager sceneManager;
	Scene* currentScene;
	std::unordered_map<int, Scene*> sceneMap;
};

