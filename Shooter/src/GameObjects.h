#pragma once
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include <iostream>
#include <initializer_list>


#include "Animation.h"
#include "Camera.h"
#include "States.h"


class GameObjects
{
public:
	virtual void DrawObject(CameraController& camera) const = 0;
	virtual void UpdateObject() const = 0;
	virtual void setCurrentAnimation(State state) = 0;
	virtual void setPosition(const Vector2& pos) = 0;
private:
};


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
		setPosition({ 358.0f, 224.0f });
	}

	void setPosition(const Vector2& pos) override
	{
		position = pos;
	}

	void setCurrentAnimation(State state) override
	{
		currentAnimation = npcAnimations[state];
	}

	void DrawObject(CameraController& camera) const override
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

			currentAnimation->DrawAnimation(adjustedPosition);
		}
	}

	void UpdateObject() const override
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
	Spritesheet* currentAnimation;
	Vector2 position;
};

