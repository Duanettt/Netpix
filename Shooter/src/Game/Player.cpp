#include "Player.h"

Player::Player() : playerState(IDLE), position{ 358.0f, 224.0f } {
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


void Player::HandleMovementInput(float worldWidth)
{

    if (isInteracting) return;

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
