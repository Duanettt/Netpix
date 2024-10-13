#include "GUI.h"

Menu::Menu() : playButton("res/UI/play_button.png")
{
	// Will be implementing either an array or vector for adding buttons to our menu.
	// Will have to make this a lot neater.
	this->background = ParallaxSceneComponent("res/background/b4/7.png");

	parallaxScene = ParallaxScene(background);

	menuMusic = LoadMusicStream("res/sounds/Tems-FreeMind.mp3");
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

