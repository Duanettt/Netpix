#include "Button.h"

Button::Button(const char* filePath)
{
	this->buttonTexture = LoadTexture(filePath);

	// Get the Height and Width of our frame for our button
	frameHeight = (float)buttonTexture.height / 2.0f;
	frameWidth = (float)buttonTexture.width;

	sourceRec = { 0.0, 0.0, frameWidth, frameHeight };

	buttonBounds = CreateButtonBoundingBox();

	//transition = Transitions(0.5f, [](float t) {return t * t; });
}

Rectangle Button::CreateButtonBoundingBox()
{
	const int screenHeight = GetScreenHeight();
	const int screenWidth = GetScreenWidth();


	// Define button bounds on screen
	Rectangle btnBounds = { screenWidth / 2.0f - buttonTexture.width / 2.0f, screenHeight / 2.0f - buttonTexture.height / 3 / 2.0f, (float)buttonTexture.width, frameHeight };

	return btnBounds;
}

void Button::Draw()
{
	DrawTextureRec(buttonTexture, sourceRec, { buttonBounds.x, buttonBounds.y }, WHITE); // Draw button frame
}

void Button::Update(Vector2 mousePoint, GameScreen& currentScreen)
{
	if (CheckCollisionPointRec(mousePoint, buttonBounds))
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			// Responsible for holding down the button.
			buttonState = 1;
		}
		else
		{
			// Responsible for our hovering button state.
			buttonState = 0;
		}

		if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
		{
			// Once the user stops pressing.
			buttonAction = true;
			std::cout << "Testing" << std::endl;
		}

	}
	else buttonState = 0;


	if (buttonAction)
	{
		currentScreen = GameScreen::GAMEPLAY;
	}
	// We now set the source rectangle based on the state of our button and increase the y position.

	sourceRec.y = buttonState * frameHeight;
}


