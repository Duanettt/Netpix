#include "GUI.h"

Menu::Menu() : playButton("UI_3")
{
	// Will be implementing either an array or vector for adding buttons to our menu.
	// Will have to make this a lot neater.
	parallaxScene = ParallaxScene("b4_7");

	menuMusic = ResourceManager::getInstance().GetResource<Music>("game_music_3");
}

void Menu::Draw()
{
	parallaxScene.DrawScene();
	playButton.Draw(); // Draw the button
	PlayMusicStream(menuMusic);
}

void Menu::Update(GameScreen& currentScreen)
{
	parallaxScene.UpdateScene();

	// Get the mouse position
	Vector2 mousePoint = GetMousePosition();
	UpdateMusicStream(menuMusic);
	playButton.Update(mousePoint, currentScreen); // Update the button with the mouse position
}

// Need to implement lots of unloading and actually get a resource manager in place.

