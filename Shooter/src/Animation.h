#pragma once
#include <raylib.h>

class Animation
{
public:
    int framesCounter = 0;

    void LoadAnimation(const char* filePath, int frameCount)
    {
        texture = LoadTexture(filePath);
        frameRec = { 0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height }; // Update frameRec after loading texture
        this->frameCount = frameCount;
    }

    void UpdateAnimation(int framesSpeed)
    {
        framesCounter++;
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame >= frameCount) currentFrame = 0;
            frameRec.x = (float)currentFrame * (float)texture.width / frameCount;
        }
    }

    void DrawAnimation(Vector2 position)
    {
        DrawTextureRec(texture, frameRec, position, WHITE);
    }

protected:
    Texture2D texture;
    int currentFrame = 0;
    int frameCount = 0;
    Rectangle frameRec;
};

class Spritesheet : public Animation
{
public:
    Spritesheet(const char* filePath, int frameCount)
    {
        LoadAnimation(filePath, frameCount); // Load the animation
    }
};

class IdleSpritesheet : public Spritesheet
{
public:
    IdleSpritesheet(const char* filePath) : Spritesheet(filePath, 6)
    {
    }
};

class RunningSpritesheet : public Spritesheet
{
public:
    RunningSpritesheet(const char* filePath) : Spritesheet(filePath, 10)
    {
    }
};

class WalkingSpritesheet : public Spritesheet
{
public:
    WalkingSpritesheet(const char* filePath) : Spritesheet(filePath, 10)
    {
    }
};

class AttackSpritesheet : public Spritesheet
{
public:
    AttackSpritesheet(const char* filePath) : Spritesheet(filePath, 4)
    {
    }
};
