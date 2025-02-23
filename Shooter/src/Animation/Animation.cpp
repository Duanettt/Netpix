#include "Animation.h"

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


void Animation::DrawAnimation(Vector2 position, bool isFacingRight) {
    Rectangle sourceRec = frameRec;
    if (!isFacingRight) {
        sourceRec.width = -frameRec.width;
    }

    // Destination rectangle with proper positioning
    Rectangle destRec = {
        position.x,
        position.y,
        frameRec.width * scale,
        frameRec.height * scale
    };

    DrawTexturePro(
        texture,
        sourceRec,
        destRec,
        origin,
        rotation,
        WHITE
    );
}

void Animation::DrawAnimation(Vector2 position, bool isFacingRight, int scale) {
    Rectangle sourceRec = frameRec;
    if (!isFacingRight) {
        sourceRec.width = -frameRec.width;
    }

    // Destination rectangle with proper positioning
    Rectangle destRec = {
        position.x - 200.0f,
        position.y - 200.0f,
        frameRec.width * scale,
        frameRec.height * scale
    };

    DrawTexturePro(
        texture,
        sourceRec,
        destRec,
        origin,
        rotation,
        WHITE
    );
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




