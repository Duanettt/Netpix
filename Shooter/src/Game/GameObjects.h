#pragma once
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include <iostream>
#include <initializer_list>


#include "../Animation/Animation.h"
#include "../Core/Camera.h"
#include "../Core/States.h"


// Game objects is an interface for constructing various objects within our game that the player will have to interact with.

class GameObjects
{
public:
	// Draws the object
	virtual void DrawObject(CameraController& camera) = 0;
	// Updates the object, animation, position etcetera;
	virtual void UpdateObject() = 0;
	// Allows us to set a state for the object.
	virtual void setCurrentAnimation(State state) = 0;
	// Allows us to set a position
	void setPosition(const Vector2& pos) 
	{
		position = pos;
	}

	Vector2& getPosition()
	{
		return position;
	}

	Rectangle GetCurrentObjectBoundingRect()
	{
		float rectangleWidth = 0;
		float rectangleHeight = 0;



		if (currentAnimation != nullptr)
		{   // We get the full texture's width and divide it by the number of frames within the texture.

			float currentFrameCount = currentAnimation->getFrameCount();
			rectangleWidth = (currentAnimation->getTextureWidth() / currentFrameCount);
			// std::cout << "This is the rectangle's width: " << rectangleWidth << std::endl;
			rectangleHeight = (currentAnimation->getTextureHeight());
			// std::cout << "This is the rectangle's height: " << rectangleWidth << std::endl;
		}

		Rectangle playerRect = Rectangle({ position.x, position.y, rectangleWidth, rectangleHeight});
		return playerRect;
	}

protected:
	Vector2 position;
	Spritesheet* currentAnimation;
};

// NPC for example now inherits from game object and we can now create an NPC object and add to our scene in the client.
class NPC : public GameObjects
{
public:
	NPC(std::unordered_map<State, Spritesheet*> spritesheets)
	{
		for (const auto& pair : spritesheets)
		{
			npcAnimations[pair.first] = pair.second;
		}

		// Set the default animation
		currentAnimation = npcAnimations[IDLE];
		setPosition({ 758.0f, 224.0f });
	}
	void setCurrentAnimation(State state) override

	{
		// set the default state of our npc.
		// we can now change the state if we need different animations to play.
		currentAnimation = npcAnimations[state];
	}

	void DrawObject(CameraController& camera) override
	{
		if (currentAnimation)
		{
			/*
			* So this is best demonstrated by example:
			* World position of NPC: is 500, 300 for example.
			* Lets say the camera moves 100 pixels to the right
			* Thats the camera offset basically 100.
			* To draw the NPC in the right place relative to the screen, you subtract the camera's position (offset) from the NPC's world position:
			* Screen position = NPC world position − Camera position
			* Screen position= NPC world position−Camera position
			* Substituting the values: (500,300) − (100,0)= (400,300)
			* (500,300)−(100,0)=(400,300)
			* So the NPC will be drawn at (400, 300) on the screen, which appears correct relative to the camera's position.
			*/
			Vector2 adjustedPosition = Vector2Subtract(position, camera.getCameraOffset());

			float npcPosition = getPosition().x;

			bool IsFacingRight = camera.getCameraDirection(npcPosition);


			currentAnimation->DrawAnimation(adjustedPosition, IsFacingRight);
		}
	}

	void UpdateObject() override
	{
		if (currentAnimation) {
			currentAnimation->UpdateAnimation(8);
		}
	}

	void Unload()
	{
		delete currentAnimation;
		currentAnimation = nullptr;
	}
private:
	std::unordered_map<State, Spritesheet*> npcAnimations;
};