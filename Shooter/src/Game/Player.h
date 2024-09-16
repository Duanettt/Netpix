#pragma once
#include <raylib.h>
#include <unordered_map>
#include "../Animation/Animation.h"
#include <iostream>
#include "../Core/States.h"

class Player {
public:
    Player();
    ~Player();

    void Update(float worldWidth);
    void Draw();
    Rectangle GetPlayerBoundingRect();
    void SetPlayerPosition(Vector2 newPosition);
    Vector2 GetPlayerPosition();
private:
    std::unordered_map<State, Spritesheet*> animations;
    State playerState;
    Vector2 position;
    bool isFacingRight = false;
    Spritesheet* currentAnimation = nullptr;

    float halfScreenWidth = GetScreenWidth() / 2;

    bool isAttacking;

    void HandleInput(float worldWidth);
    void HandleMovementInput(float worldWidth);
    bool HandleMouseInput();
    void SetPlayerState(State state);
};
