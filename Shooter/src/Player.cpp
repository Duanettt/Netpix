#include "Player.h"

Player::Player() : playerState(IDLE), position{ 358.0f, 224.0f } {
    animations[IDLE] = new IdleSpritesheet();
    animations[WALKING] = new WalkingSpritesheet();
    animations[RUNNING] = new RunningSpritesheet();
    animations[ATTACK] = new AttackSpritesheet();

    // Set the initial animation
    currentAnimation = animations[IDLE];
}

Player::~Player() {
    for (auto& pair : animations) {
        delete pair.second;
    }
}

void Player::Update() {
    HandleInput();
    if (currentAnimation) {
        currentAnimation->UpdateAnimation(8);
    }
}

void Player::Draw() {
    if (currentAnimation) {
        currentAnimation->DrawAnimation(position);
    }
}

void Player::SetPlayerPosition(Vector2 newPosition)
{
    position = newPosition;
}

Vector2 Player::GetPlayerPosition()
{
    return position;
}

void Player::HandleInput() 
{
    isAttacking = HandleMouseInput();

    if (!isAttacking)
    {
        HandleMovementInput();
    }
}

void Player::HandleMovementInput()
{
    SetPlayerState(IDLE);



    if (IsKeyDown(KEY_S) && position.y <= 275.0f)
    {
        position.y += 2.0f;
        SetPlayerState(WALKING);
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            position.y += 2.7f;
            SetPlayerState(RUNNING);
        }
    }
    if (IsKeyDown(KEY_W) && position.y >= 190.0f)
    {
        position.y -= 2.0f;
        SetPlayerState(WALKING);
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            position.y -= 2.7f;
            SetPlayerState(RUNNING);
        }
    }
    if (IsKeyDown(KEY_D))
    {
        position.x += 2.0f;
        SetPlayerState(WALKING);
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            position.x += 2.7f;
            SetPlayerState(RUNNING);
        }
    }
    if (IsKeyDown(KEY_A))
    {
        position.x -= 2.0f;
        SetPlayerState(WALKING);
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            position.x -= 2.7f;
            SetPlayerState(RUNNING);
        }
    }
}

bool Player::HandleMouseInput()
{
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        SetPlayerState(ATTACK);
        return true;
    }
    return false;
}



void Player::SetPlayerState(PlayerState state) {
    if (playerState != state) {
        playerState = state;
        currentAnimation = animations[playerState];
    }
}
