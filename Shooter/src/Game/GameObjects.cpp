#include "GameObjects.h"
#include <iostream>

// Implementation of GameObjects methods

void GameObjects::setPosition(const Vector2& pos)
{
    position = pos;
}

Vector2& GameObjects::getPosition()
{
    return position;
}

Rectangle GameObjects::GetCurrentObjectBoundingRect() {
    float rectangleWidth = 0;
    float rectangleHeight = 0;

    if (currentAnimation != nullptr)
    {
        // We get the full texture's width and divide it by the number of frames within the texture.
        float currentFrameCount = currentAnimation->getFrameCount();
        rectangleWidth = (currentAnimation->getTextureWidth() / currentFrameCount);
        rectangleHeight = (currentAnimation->getTextureHeight());
    }

    Rectangle playerRect = Rectangle({ position.x, position.y, rectangleWidth, rectangleHeight });
    return playerRect;
}

// Implementation of NPC methods

NPC::NPC(std::unordered_map<State, Spritesheet*> spritesheets)
{
    for (const auto& pair : spritesheets)
    {
        npcAnimations[pair.first] = pair.second;
    }

    // Set the default animation
    currentAnimation = npcAnimations[IDLE];
    setPosition({ 758.0f, 224.0f });
}

void NPC::setCurrentAnimation(State state)
{
    // Set the default state of our NPC.
    // We can now change the state if we need different animations to play.
    currentAnimation = npcAnimations[state];
}

void NPC::DrawObject(CameraController& camera)
{
    if (currentAnimation)
    {
        // Adjust NPC position based on the camera's offset.
        Vector2 adjustedPosition = Vector2Subtract(position, camera.getCameraOffset());

        float npcPosition = getPosition().x;

        bool IsFacingRight = camera.getCameraDirection(npcPosition);

        currentAnimation->DrawAnimation(adjustedPosition, IsFacingRight);
    }
}

void NPC::UpdateObject()
{
    if (currentAnimation) {
        currentAnimation->UpdateAnimation(8);
    }
}

void NPC::Unload()
{
    delete currentAnimation;
    currentAnimation = nullptr;
}

