#pragma once
#include <raylib.h>
#include <iostream>

/* 
The animation class is responsible for our animations. It allows for our game objects class to utilise this and create animations
.
*/

class Animation
{
public:
    int framesCounter = 0;

    // Load animation essentially loads our animation into a texture member variable.
    void LoadAnimation(const char* filePath, int frameCount)
    {
        texture = LoadTexture(filePath);
        // Frame rectangle used for drawing an animation frame by frame.
        frameRec = { 0.0f, 0.0f, (float)texture.width / frameCount, (float)texture.height };
        this->frameCount = frameCount;
    }

    void UpdateAnimation(int framesSpeed)
    {
        // counts how many frames.
        framesCounter++;

        // This check allows for us to determine the rate at which the frameRec moves over our spritesheet.
        if (framesCounter >= (60 / framesSpeed))
        {
            framesCounter = 0;
            currentFrame++;
            if (currentFrame >= frameCount) currentFrame = 0;
            // Moves the frame.
            frameRec.x = (float)currentFrame * (float)texture.width / frameCount;
        }
    }
    void DrawAnimation(Vector2 position, bool isFacingRight) {
        // Had a lot of trouble with this but ChatGPT helped..
        /*
        * The main thing was understanding what was going on with the frameRec
        * frameRec itself was handling the updating of our spritesheet. When we negated that it completely
        * changed the way we rendered our spritesheet
        * So instead we had to assign a temporary rectangle to allow for us to perform transformations on a specific frame.
        */
        Rectangle sourceRec = frameRec;
        if (!isFacingRight) {
            // Flip the sprite horizontally if not facing right
            // Distinguishes between left and right for our player.
            sourceRec.width = -frameRec.width;
        }

        DrawTextureRec(texture, sourceRec, position, WHITE);
    }


    void DrawAnimation(Vector2 position)
    {
        // Basic draw call for each animation.
        DrawTextureRec(texture, frameRec, position, WHITE);
    }


protected:
    Texture2D texture;
    Rectangle frameRec;
    int currentFrame = 0;
    int frameCount = 0;
    float temp = 0.0f;
};


// The spritesheets are useful for creating various different spritesheets and allows us to construct a spritesheet
// for our own specific use.
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
