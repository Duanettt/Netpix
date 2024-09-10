#pragma once
#include <raylib.h>
#include <unordered_map>
#include "Animation.h"
#include <iostream>
#include "States.h"

class Player {
public:
    Player();
    ~Player();

    void Update();
    void Draw();

    void SetPlayerPosition(Vector2 newPosition);
    Vector2 GetPlayerPosition();
private:
    std::unordered_map<State, Spritesheet*> animations;
    State playerState;
    Vector2 position;
    Spritesheet* currentAnimation = nullptr;

    bool isAttacking;

    void HandleInput();
    void HandleMovementInput();
    bool HandleMouseInput();
    void SetPlayerState(State state);
};
