#pragma once
#include <raylib.h>
#include <unordered_map>
#include "../Animation/Animation.h"
#include <iostream>
#include "../Core/States.h"
#include "../ResourceManager.h"
#include "../Game/GameObjects.h"

#define SPRINT_MULTIPLIER 2.5f
#define BASE_MOVE_SPEED 100.0f

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
    void SetCollisionDetected(bool col);
    GameObjects* GetActiveObject();
    Vector2 GetPlayerPosition();

    bool IsInteracting();

    void SetAttackCooldownDuration(float duration);

    void SetAttackCooldown(bool attackCooldown);

private:
    GameObjects* activeObject = nullptr;
    std::unordered_map<State, Spritesheet*> animations;
    State playerState;
    State currentState = State::IDLE;
    Vector2 position;
    float attackCooldownTimer = 0.0f;           // Current cooldown timer
    float attackCooldownDuration = 0.5f;        // Duration of cooldown in seconds
    bool isAttackOnCooldown = false;            // Flag to track if attack is on cooldown
    bool isFacingRight = false;
    bool inventoryDetected = false;
    Spritesheet* currentAnimation = nullptr;
    float halfScreenWidth = GetScreenWidth() / 2;
    bool isAttacking = false;
    bool isInteracting = false;
    bool collisionDetected = false;
    void HandleInput(float worldWidth);
    void HandleMovementInput(float worldWidth);
    bool HandleMouseInput();
    void SetPlayerState(State state);
    void CheckStatePriority(State state);
    //void DrawPlayerOnGrid(Pathfinding& pathfinding);
};
