#pragma once
#include <raylib.h>
#include <iostream>

#include "../Core/States.h"
#include "../Animation/Transitions.h"
#include "../ResourceManager.h"

class Button
{
public:
	Rectangle buttonBounds;
	int buttonState;
	bool buttonAction = false;
	float frameHeight;
	float frameWidth;
	Rectangle sourceRec;
	//Transitions transition;

	//Button(const char* filePath);
	Button(const char* buttonTextureKey);

	// Button Methods
	

	Rectangle CreateButtonBoundingBox();
	void SetButtonState();
	void SetButtonAction();
	void Draw();
	void Update(Vector2 mousePoint, GameScreen& currentScreen);
private:
	Texture2D buttonTexture;
 };


