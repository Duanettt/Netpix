#include "Player.h"
#include "../Scene/Scene.h"

Player::Player() : playerState(IDLE), position{ 358.0, 224.0f } {
    animations[IDLE] = new IdleSpritesheet(std::string("main_4"), 6);
    animations[WALKING] = new WalkingSpritesheet(std::string("main_6"), 10);
    animations[RUNNING] = new RunningSpritesheet(std::string("main_5"), 10);
    animations[ATTACK] = new AttackSpritesheet(std::string("main_1"),4);

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

        if (inventoryDetected)
        {
            DrawRectangle(0, 400, 500, 500, BLACK);
        }
        currentAnimation->DrawAnimation(position, isFacingRight);

        Rectangle playerRect = GetPlayerBoundingRect();

        DrawRectangle(playerRect.x, playerRect.y, playerRect.width,playerRect.height, RED);
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
    
    Rectangle playerRect = Rectangle({ position.x + 20, position.y + 70, rectangleWidth - 50, rectangleHeight - 70});
    return playerRect;
}


void Player::SetIsInteracting(bool value)
{
    isInteracting = value;
}
void Player::SetPlayerPosition(Vector2 newPosition)
{
    position = newPosition;
}

void Player::SetActiveObject(GameObjects* object)
{
    activeObject = object;
}

void Player::SetCollisionDetected(bool col)
{
    collisionDetected = col;
}

GameObjects* Player::GetActiveObject()
{
    return activeObject;
}

Vector2 Player::GetPlayerPosition()
{
    return position;
}

bool Player::IsInteracting()
{
    return isInteracting;
}

void Player::HandleInput(float worldWidth) 
{
    isAttacking = HandleMouseInput();

    if (!isAttacking)
    {
        HandleMovementInput(worldWidth);
    }

    if (IsKeyPressed(KEY_TAB))
    {
        std::cout << "Tab detected" << std::endl;
        inventoryDetected = !inventoryDetected;
    }

    if (IsKeyPressed(KEY_E) && activeObject)
    {
        // How we invoke function calls in other methods without coupling too much.
        isInteracting = true;
    }
}


void Player::HandleMovementInput(float worldWidth) {
    float delta = GetFrameTime();

    if (isInteracting || collisionDetected) return;

    SetPlayerState(IDLE);
    float currentSpeed = BASE_MOVE_SPEED;

    if (IsKeyDown(KEY_LEFT_SHIFT)) {
        currentSpeed *= SPRINT_MULTIPLIER;
    }

    Vector2 moveDirection = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_S) && position.y <= 275.0f) {
        moveDirection.y = 1.0f;
        SetPlayerState(IsKeyDown(KEY_LEFT_SHIFT) ? RUNNING : WALKING);
    }
    if (IsKeyDown(KEY_W) && position.y > 190.0f) {
        moveDirection.y = -1.0f;
        SetPlayerState(IsKeyDown(KEY_LEFT_SHIFT) ? RUNNING : WALKING);
    }
    if (IsKeyDown(KEY_D) && position.x <= worldWidth - 25.0f) {
        moveDirection.x = 1.0f;
        isFacingRight = true;
        SetPlayerState(IsKeyDown(KEY_LEFT_SHIFT) ? RUNNING : WALKING);
    }
    if (IsKeyDown(KEY_A) && position.x >= 0) {
        moveDirection.x = -1.0f;
        isFacingRight = false;
        SetPlayerState(IsKeyDown(KEY_LEFT_SHIFT) ? RUNNING : WALKING);
    }

    // Normalize diagonal movement
    if (moveDirection.x != 0.0f && moveDirection.y != 0.0f) {
        float length = sqrt(moveDirection.x * moveDirection.x + moveDirection.y * moveDirection.y);
        moveDirection.x /= length;
        moveDirection.y /= length;
    }

    // Apply movement
    position.x += moveDirection.x * currentSpeed * delta;
    position.y += moveDirection.y * currentSpeed * delta;
}



bool Player::HandleMouseInput()
{
    if (isInteracting) return false;

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        //std::cout << "Click detected!" << std::endl;
        SetPlayerState(ATTACK);
        return true;
    }
    return false;
}



void Player::SetPlayerState(State state) {

    if (playerState != state) {
        playerState = state;
        CheckStatePriority(playerState);
        currentAnimation = animations[playerState];
    }
}

void Player::CheckStatePriority(State state)
{
    // PROBLEM: The animation class plays based on holding instead of clicking in animation we need to build a new way of animating so when the user clicks it plays the full animation.. So its when the user released the click.
    // This checks for our players current state based on the user input.

    // Somewhat solved -- We have the basic attack.
    if (currentState < state)
    {
        // We print out our state
        std::cout << currentState << "\n" << std::endl;
        // Find the time taken for our attack state to finish the animation.

        currentState = state;
        std::cout << "New state is greater than the previous state!";

        // Now successfully checks which state is greater than which.
        // One issue: If we start walking 
    }
}

