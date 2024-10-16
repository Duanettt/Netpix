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

// Derived classes constructors
IdleSpritesheet::IdleSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}
RunningSpritesheet::RunningSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}
WalkingSpritesheet::WalkingSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}
AttackSpritesheet::AttackSpritesheet(const char* filePath, int frameCount) : Spritesheet(filePath, frameCount) {}


