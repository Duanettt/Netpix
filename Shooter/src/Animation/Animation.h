#pragma once
#include <raylib.h>

// The animation class is responsible for handling animations for game objects
class Animation
{
public:
    Animation() = default;
    virtual ~Animation() = default;

    // Load animation by loading texture and setting up frame rectangle
    void LoadAnimation(const char* filePath, int frameCount);

    // Update animation frame based on speed
    void UpdateAnimation(int framesSpeed);
    void UpdateAnimation(int framesSpeed, Rectangle playerBox);

    // Draw animation at given position and direction
    void DrawAnimation(Vector2 position, bool isFacingRight);
    void DrawAnimation(Vector2 position);

    // Getters for texture dimensions and frame count
    float getTextureWidth();
    float getTextureHeight();
    int getFrameCount();

protected:
    Texture2D texture{};
    Rectangle frameRec{};
    int framesCounter = 0;
    int currentFrame = 0;
    int frameCount = 0;
};

// Derived classes for different spritesheets
class Spritesheet : public Animation
{
public:
    Spritesheet(const char* filePath, int frameCount);
};

class IdleSpritesheet : public Spritesheet
{
public:
    IdleSpritesheet(const char* filePath, int frameCount);
};

class RunningSpritesheet : public Spritesheet
{
public:
    RunningSpritesheet(const char* filePath, int frameCount);
};

class WalkingSpritesheet : public Spritesheet
{
public:
    WalkingSpritesheet(const char* filePath, int frameCount);
};

class AttackSpritesheet : public Spritesheet
{
public:
    AttackSpritesheet(const char* filePath, int frameCount);
};
;