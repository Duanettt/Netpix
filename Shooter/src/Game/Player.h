#pragma once
#include <raylib.h>
#include <unordered_map>
#include "../Animation/Animation.h"
#include <iostream>
#include "../Core/States.h"
#include "../ResourceManager.h"
#include "../Game/GameObjects.h"

class Player {
public:
    Player();
    ~Player();

    void Update(float worldWidth);
    void Draw();
    Rectangle GetPlayerBoundingRect();
    void SetIsInteracting(bool value);
    void SetPlayerPosition(Vector2 newPosition);
    void SetActiveObject(GameObjects* object);
    GameObjects* GetActiveObject();
    Vector2 GetPlayerPosition();

    bool IsInteracting();

private:

    GameObjects* activeObject = nullptr;
    std::unordered_map<State, Spritesheet*> animations;
    State playerState;
    State currentState = State::IDLE;
    Vector2 position;
    bool isFacingRight = false;
    bool inventoryDetected = false;
    Spritesheet* currentAnimation = nullptr;

    float halfScreenWidth = GetScreenWidth() / 2;

    bool isAttacking = false;
    bool isInteracting = false;

    void HandleInput(float worldWidth);
    void HandleMovementInput(float worldWidth);
    bool HandleMouseInput();
    void SetPlayerState(State state);
    void CheckStatePriority(State state);
};
