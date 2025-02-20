#include "GameObjects.h"
#include <iostream>
#include "Player.h"


// Implementation of GameObjects methods

void GameObjects::setPosition(const Vector2& pos)
{
    this->position = pos;
}

Vector2& GameObjects::getPosition()
{
    return position;
}

Rectangle GameObjects::GetCurrentObjectBoundingRect()
{
    float rectangleWidth = 0;
    float rectangleHeight = 0;

    if (currentAnimation != nullptr)
    {
        // We get the full texture's width and divide it by the number of frames within the texture.
        float currentFrameCount = currentAnimation->getFrameCount();
        rectangleWidth = (currentAnimation->getTextureWidth() / currentFrameCount);
        rectangleHeight = (currentAnimation->getTextureHeight());
    }
    // CameraAdjustedPosition  needs to be implemented here for collision detection.
    Rectangle objectRect = Rectangle({ cameraAdjustedPosition.x, cameraAdjustedPosition.y, rectangleWidth, rectangleHeight });

    return objectRect;
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

    dialogues = { "Hello!", "Welcome to the game.", "Goodbye!" };
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

        cameraAdjustedPosition = adjustedPosition;

        float npcPosition = getPosition().x;

        bool IsFacingRight = camera.getCameraDirection(npcPosition);

        currentAnimation->DrawAnimation(adjustedPosition, IsFacingRight);

        Rectangle rect = this->GetCurrentObjectBoundingRect();

        // See the size of our rectangle height, width
        //DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);

    }
}
void NPC::DrawObject(CameraController& camera, Vector2 screenPosition, int scaleFactor)
{
    // This method as of right now is specifically for dialogues.
    if (currentAnimation)
    {
        // Adjust NPC position based on the camera's offset.
        float npcPosition = getPosition().x;

      

        bool IsFacingRight = camera.getCameraDirection(npcPosition);

        currentAnimation->DrawAnimation(screenPosition, IsFacingRight);

        // See the size of our rectangle height, width
        //DrawRectangle(rect.x, rect.y, rect.width, rect.height, RED);

    }
}

void NPC::DrawDialogueSprite(int scaleFactor)
{
    if (currentAnimation)
    {
        // Always face right during dialogues (or set based on your logic)
        bool isFacingRight = true;
        Vector2 npcScreenPosition = { 0.0f, 0.0f };
        // Render the NPC sprite at a fixed screen-space position
        currentAnimation->DrawAnimation(npcScreenPosition, isFacingRight);
    }
}
 
Rectangle NPC::GetCurrentObjectBoundingRect()
{
    float rectangleWidth = 0;
    float rectangleHeight = 0;

    if (currentAnimation != nullptr)
    {
        // We get the full texture's width and divide it by the number of frames within the texture.
        float currentFrameCount = currentAnimation->getFrameCount();
        rectangleWidth = (currentAnimation->getTextureWidth() / currentFrameCount) - 75.0f;
        rectangleHeight = (currentAnimation->getTextureHeight());
    }
    // CameraAdjustedPosition  needs to be implemented here for collision detection.
    Rectangle npcRect = Rectangle({ cameraAdjustedPosition.x + 45.0f, cameraAdjustedPosition.y + 30.0f, rectangleWidth, rectangleHeight - 30.0f });

    return npcRect;
}

void NPC::UpdateAI(Player& player) {
    if (!isAggressive) return;

    float delta = GetFrameTime();
    Vector2 playerPos = player.GetPlayerPosition();

    float distToPlayer = Vector2Distance(cameraAdjustedPosition, playerPos);
    std::cout << "NPC position: " << position.x << std::endl;
   

    // Remove this check since it will rarely be exactly 0
    // if (distToPlayer == 0) {
    //     setCurrentAnimation(IDLE);
    //     return;
    // }

    // Add a minimum distance to prevent jittering when very close
    const float MIN_DISTANCE = 40.0f;  // Adjust this value as needed
    // Only move if we're not too close to the player
    if (distToPlayer > MIN_DISTANCE) {
        setCurrentAnimation(WALKING);
        Vector2 direction = Vector2Subtract(playerPos, cameraAdjustedPosition);

        // Normalize direction vector
        float length = sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0) {
            direction.x /= length;
            direction.y /= length;
        }

        // Optional: Add variable speed based on distance
        float speedMultiplier = 1.0f;
        if (distToPlayer > FOLLOW_DISTANCE * 0.7f) {
            // Move faster when further away
            speedMultiplier = 1.25f;
        }

        // Apply movement with delta time
        position.x += direction.x * BASE_MOVE_SPEED * speedMultiplier * delta;
        position.y = Clamp(
            position.y + direction.y * BASE_MOVE_SPEED * speedMultiplier * delta,
            190.0f,  // Minimum Y
            275.0f   // Maximum Y
        );
    }
    else {
        setCurrentAnimation(IDLE);
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

std::vector<const char*> NPC::getDialogueLines()
{
    return dialogues;
}

