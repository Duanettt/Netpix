#include "Player.h"

Player::Player() : playerState(IDLE), position{ 358.0f, 224.0f } {
    animations[IDLE] = new IdleSpritesheet("res/character/main/idle.png",6);
    animations[WALKING] = new WalkingSpritesheet("res/character/main/Walk.png",10);
    animations[RUNNING] = new RunningSpritesheet("res/character/main/Run.png",10);
    animations[ATTACK] = new AttackSpritesheet("res/character/main/Attack.png",10);

    // Set the initial animation
    currentAnimation = animations[IDLE];
}

Player::~Player() {
    for (auto& pair : animations) {
        delete pair.second;
    }
}

void Player::Update(float worldWidth) {
    HandleInput(worldWidth);
    if (currentAnimation) {
        currentAnimation->UpdateAnimation(8);
    }
}

void Player::Draw() {
    if (currentAnimation) {
        currentAnimation->DrawAnimation(position, isFacingRight);
    }
}

Rectangle Player::GetPlayerBoundingRect()
{
    float rectangleWidth = 0;
    float rectangleHeight = 0;

    

    if (currentAnimation != nullptr)
    {   // We get the full texture's width and divide it by the number of frames within the texture.

        float currentFrameCount = currentAnimation->getFrameCount();
        rectangleWidth = (currentAnimation->getTextureWidth() / currentFrameCount);
        // std::cout << "This is the players width: " << rectangleWidth << std::endl;
        rectangleHeight = (currentAnimation->getTextureHeight());
        // std::cout << "This is the players height: " << rectangleWidth << std::endl;
    }
    
    Rectangle playerRect = Rectangle({ position.x, position.y, rectangleWidth, rectangleHeight });
    return playerRect;
}

void Player::SetPlayerPosition(Vector2 newPosition)
{
    position = newPosition;
}

Vector2 Player::GetPlayerPosition()
{
    return position;
}

void Player::HandleInput(float worldWidth) 
{
    isAttacking = HandleMouseInput();

    if (!isAttacking)
    {
        HandleMovementInput(worldWidth);
    }
}

void Player::HandleMovementInput(float worldWidth)
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
    if (IsKeyDown(KEY_D) && position.x <= worldWidth - 25.0f)
    {
        isFacingRight = true;
        position.x += 2.0f;
        SetPlayerState(WALKING);
        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            position.x += 2.7f;
            SetPlayerState(RUNNING);
        }
    }
    if (IsKeyDown(KEY_A) && position.x >= 0)
    {
        isFacingRight = false;
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



void Player::SetPlayerState(State state) {
    if (playerState != state) {
        playerState = state;
        currentAnimation = animations[playerState];
    }
}
