#pragma once
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include "../Animation/Animation.h"
#include "../Core/Camera.h"
#include "../Core/States.h"

// GameObjects is an interface for constructing various objects within our game that the player will have to interact with.

class GameObjects
{
public:
    // Draws the object
    virtual void DrawObject(CameraController& camera) = 0;
    // Updates the object, animation, position, etc.
    virtual void UpdateObject() = 0;
    // Allows us to set a state for the object.
    virtual void setCurrentAnimation(State state) = 0;
    // Allows us to set a position
    void setPosition(const Vector2& pos);

    Vector2& getPosition();
    Rectangle GetCurrentObjectBoundingRect();
protected:
    Vector2 position;
    Vector2 cameraAdjustedPosition;
    Spritesheet* currentAnimation;
};

// NPC inherits from GameObjects and we can now create an NPC object and add it to our scene in the client.
class NPC : public GameObjects
{
public:
    NPC(std::unordered_map<State, Spritesheet*> spritesheets);
    void setCurrentAnimation(State state) override;
    void DrawObject(CameraController& camera) override;
    void UpdateObject() override;
    void Unload();

private:
    std::unordered_map<State, Spritesheet*> npcAnimations;
};
