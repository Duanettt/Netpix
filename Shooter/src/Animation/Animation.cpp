#include "Animation.h"


#include "Animation.h"
#include <iostream>

// Load animation by setting up texture and frame rectangle
void Animation::LoadAnimation(const char* filePath, int frameCount)
{
    texture = LoadTexture(filePath);
    frameRec = { 0.0f, 0.0f, static_cast<float>(texture.width) / frameCount, static_cast<float>(texture.height) };
    this->frameCount = frameCount;
}

void Animation::LoadAnimation(Texture2D& userTexture, int frameCount)
{
    texture = userTexture;
    frameRec = { 0.0f, 0.0f, static_cast<float>(texture.width) / frameCount, static_cast<float>(texture.height) };
    this->frameCount = frameCount;
}


// Update animation frame based on speed
void Animation::UpdateAnimation(int framesSpeed)
{
    framesCounter++;
    if (framesCounter >= (60 / framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;
        if (currentFrame >= frameCount) currentFrame = 0;
        frameRec.x = static_cast<float>(currentFrame) * static_cast<float>(texture.width) / frameCount;
    }
}

// Update animation with playerBox parameter
void Animation::UpdateAnimation(int framesSpeed, Rectangle playerBox)
{
    framesCounter++;
    std::cout << framesCounter << std::endl;

    if (framesCounter >= (60 / framesSpeed))
    {
        framesCounter = 0;
        currentFrame++;
        if (currentFrame >= frameCount) currentFrame = 0;
        frameRec.x = static_cast<float>(currentFrame) * static_cast<float>(texture.width) / frameCount;
    }
}

// Draw animation at given position and flip based on direction
void Animation::DrawAnimation(Vector2 position, bool isFacingRight)
{
    Rectangle sourceRec = frameRec;
    if (!isFacingRight)
    {
        sourceRec.width = -frameRec.width;
    }
    DrawTextureRec(texture, sourceRec, position, WHITE);
}

void Animation::DrawAnimation(Vector2 position, bool isFacingRight, int scaleFactor)
{
    Rectangle sourceRec = frameRec;
    if (!isFacingRight)
    {
        sourceRec.width = -frameRec.width;
    }

    texture.width = texture.width * scaleFactor;
    texture.height = texture.height * scaleFactor;

    DrawTextureRec(texture, sourceRec, position, WHITE);
}

// Basic draw call for animation
void Animation::DrawAnimation(Vector2 position)
{
    DrawTextureRec(texture, frameRec, position, WHITE);
}

// Getters for texture dimensions and frame count
float Animation::getTextureWidth()
{
    return texture.width;
}

float Animation::getTextureHeight()
{
    return texture.height;
}

int Animation::getFrameCount()
{
    return frameCount;
}

// Spritesheet constructors
Spritesheet::Spritesheet(const char* filePath, int frameCount)
{
    LoadAnimation(filePath, frameCount);
}

Spritesheet::Spritesheet(std::string userPrompt, int frameCount)
{
    LoadAnimation(ResourceManager::getInstance().GetResource<Texture2D>(userPrompt), frameCount);
}

// Derived classes constructors
// Constructors for regular path loading.
IdleSpritesheet::IdleSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}
RunningSpritesheet::RunningSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}
WalkingSpritesheet::WalkingSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}
AttackSpritesheet::AttackSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}

// Testing with resource manager
IdleSpritesheet::IdleSpritesheet(std::string userPrompt, int frameCount) : Spritesheet(userPrompt, frameCount) {}
RunningSpritesheet::RunningSpritesheet(std::string userPrompt, int frameCount) : Spritesheet(userPrompt, frameCount) {}
WalkingSpritesheet::WalkingSpritesheet(std::string userPrompt, int frameCount) : Spritesheet(userPrompt, frameCount) {}
AttackSpritesheet::AttackSpritesheet(std::string userPrompt, int frameCount) : Spritesheet(userPrompt, frameCount) {}




