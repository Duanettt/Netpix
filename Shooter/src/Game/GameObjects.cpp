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
    void HandleCollisionResponse(GameObjects* other, float delta);
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
        currentAnimation->DrawAnimation(npcScreenPosition, isFacingRight, 5);
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

        float speedMultiplier = 1.0f;
        // This could be for sprinting
        if (distToPlayer > FOLLOW_DISTANCE) {
            // Move faster when further away
            speedMultiplier = 1.75f;
            setCurrentAnimation(RUNNING);
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

void NPC::HandleCollisionResponse(Player& other, float delta) {
    // Calculate the vector between the two objects
    Vector2 otherPosition = other.GetPlayerPosition();
    Vector2 direction = Vector2Subtract(otherPosition, this->cameraAdjustedPosition);
    float distance = Vector2Length(direction);

    // Only apply pushing force if objects are too close
    if (distance < MIN_SEPARATION_DISTANCE && distance > 0) {
        // Normalize the direction vector
        direction.x /= distance;
        direction.y /= distance;

        // Calculate push force based on how close the objects are
        float pushStrength = (MIN_SEPARATION_DISTANCE - distance) / MIN_SEPARATION_DISTANCE * PUSH_FORCE;

        // Apply the push force to both objects in opposite directions
        Vector2 push = {
            direction.x * pushStrength * delta,
            direction.y * pushStrength * delta
        };

        // Move objects apart
        this->position = Vector2Subtract(this->position, push);
        otherPosition = Vector2Add(otherPosition, push);

        // Clamp Y positions to stay within boundaries
        this->position.y = Clamp(this->position.y, 190.0f, 275.0f);
        otherPosition.y = Clamp(otherPosition.y, 190.0f, 275.0f);
    }
}


void NPC::HandleIntercollisionResponse(std::vector<NPC*>& npcVec) {

    float delta = GetFrameTime();
    // Skip if this is the only NPC
    if (npcVec.size() <= 1) return;

    for (NPC* otherNPC : npcVec) {
        // Skip checking collision with self
        if (otherNPC == this) continue;

        // Get the rectangles for collision check
        Rectangle thisRect = this->GetCurrentObjectBoundingRect();
        Rectangle otherRect = otherNPC->GetCurrentObjectBoundingRect();

        // Check if NPCs are colliding
        if (CheckCollisionRecs(thisRect, otherRect)) {
            // Calculate centers of both NPCs
            Vector2 thisCenter = {
                thisRect.x + thisRect.width / 2,
                thisRect.y + thisRect.height / 2
            };
            Vector2 otherCenter = {
                otherRect.x + otherRect.width / 2,
                otherRect.y + otherRect.height / 2
            };

            // Calculate separation vector
            Vector2 direction = Vector2Subtract(thisCenter, otherCenter);
            float distance = Vector2Length(direction);

            // Avoid division by zero
            if (distance > 0) {
                // Normalize direction
                direction.x /= distance;
                direction.y /= distance;

                // Calculate push force based on overlap
                float overlap = (MIN_SEPARATION_DISTANCE - distance);
                if (overlap > 0) {
                    float pushStrength = overlap * PUSH_FORCE * delta;

                    // Calculate push vector
                    Vector2 push = {
                        direction.x * pushStrength,
                        direction.y * pushStrength
                    };

                    // Apply push to both NPCs in opposite directions
                    // Move this NPC away
                    this->position = Vector2Add(this->position, push);
                    // Move other NPC away
                    otherNPC->position = Vector2Subtract(otherNPC->position, push);

                    // Clamp both NPCs to valid Y positions
                    this->position.y = Clamp(this->position.y, 190.0f, 275.0f);
                    otherNPC->position.y = Clamp(otherNPC->position.y, 190.0f, 275.0f);
                }
            }
        }
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
