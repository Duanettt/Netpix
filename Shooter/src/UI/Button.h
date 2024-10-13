#pragma once
#include <raylib.h>
#include <iostream>

#include "../Core/States.h"

class Button
{
public:
	Rectangle buttonBounds;
	int buttonState;
	bool buttonAction = false;
	float frameHeight;
	float frameWidth;
	Rectangle sourceRec;

	Button(const char* filePath);

	// Button Methods

	Rectangle CreateButtonBoundingBox();
	void SetButtonState();
	void SetButtonAction();
	void Draw();
	void Update(Vector2 mousePoint, GameScreen& currentScreen);
private:
	Texture2D buttonTexture;
 };


