#pragma once
#include <raylib.h>
#include <unordered_map>
#include "Animation.h"
#include <iostream>

enum PlayerState {
    IDLE = 0,
    WALKING = 1,
    RUNNING = 2,
    JUMPING = 3,
    ATTACK = 4,
};

class Player {
public:
    Player();
    ~Player();

    void Update();
    void Draw();

    void SetPlayerPosition(Vector2 newPosition);
    Vector2 GetPlayerPosition();
private:
    std::unordered_map<PlayerState, Spritesheet*> animations;
    PlayerState playerState;
    Vector2 position;
    Spritesheet* currentAnimation = nullptr;

    bool isAttacking;

    void HandleInput();
    void HandleMovementInput();
    bool HandleMouseInput();
    void SetPlayerState(PlayerState state);
};
