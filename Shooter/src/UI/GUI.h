#pragma once
#include <raylib.h>
#include <iostream>

#include "../Core/States.h"
#include "../Scene/temp/ParallaxScene.h"
#include "./Button.h"
#include "../ResourceManager.h"

#define NUM_FRAMES 3;


class GUI
{

};

class Menu
{
public:
	Menu();
	void Draw();
	void Update(GameScreen& currentScreen);
private:
	ParallaxScene parallaxScene;
	Button playButton; 
	Music menuMusic;
};

