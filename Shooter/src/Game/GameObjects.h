#pragma once
#include <raylib.h>
#include <raymath.h>
#include <unordered_map>
#include "../Animation/Animation.h"
#include "../Core/Camera.h"
#include "../Core/States.h"


// GameObjects is an interface for constructing various objects within our game that the player will have to interact with.

class Player;

class Interactable
{
public:
    virtual void Interact(const std::string prompt) = 0;
    virtual ~Interactable() = default;
private:
};

class GameObjects : public Interactable
{
public:
    // Draws the object
    virtual void DrawObject(CameraController& camera) = 0;
    // Updates the object, animation, position, etc.
    virtual void UpdateObject() = 0;
    // Allows us to set a state for the object.
    virtual void setCurrentAnimation(State state) = 0;

    virtual void Unload() = 0;
    // Allows us to set a position
    void setPosition(const Vector2& pos);


    void Interact(const std::string prompt) override
    {
        std::cout << prompt << std::endl;
    }
    Vector2& getPosition();
    Vector2 cameraAdjustedPosition;
    virtual Rectangle GetCurrentObjectBoundingRect();


protected:
    Vector2 position;
    Spritesheet* currentAnimation;
    // Variables
    const float PUSH_FORCE = 300.0f;
    const float MIN_SEPARATION_DISTANCE = 40.0f;
};

// NPC inherits from GameObjects and we can now create an NPC object and add it to our scene in the client.
class NPC : public GameObjects
{
public:
    NPC(std::unordered_map<State, Spritesheet*> spritesheets);
    void setCurrentAnimation(State state) override;
    void DrawObject(CameraController& camera) override;
    void DrawObject(CameraController& camera, Vector2 screenPosition, int scaleFactor);
    void DrawDialogueSprite(int scaleFactor);
    void DrawObject(CameraController& camera, Vector2 screenPosition);


    Rectangle GetCurrentObjectBoundingRect() override;
    void UpdateAI(Player& player);
    //void HandleIntercollisionResponse(std::vector<NPC*>& npcVec, float delta);
    void HandleIntercollisionResponse(std::vector<NPC*>& npcVec);
    void UpdateObject() override;
    void HandleCollisionResponse(Player& other, float delta);
    void Unload();
    std::vector<const char*> getDialogueLines();

    std::vector<const char*> dialogues;


    enum AIState {
        PATROL,
        CHASE,
        ATTACK,
        RETREAT
    } aiState = PATROL;

    struct Stats {
        float health = 100.0f;
        float damage = 10.0f;
        float attackSpeed = 1.0f;
        float attackRange = 50.0f;
        float detectionRange = 200.0f;
    } stats;

    const float FOLLOW_DISTANCE = 100.0f;    // Distance at which NPC starts following
    const float ATTACK_RANGE = 50.0f;        // Distance at which NPC attacks
    const float MOVEMENT_SPEED = 1.0f;       // How fast the NPC moves
    const float BASE_MOVE_SPEED = 120.0f;
    float attackCooldown = 0.0f;             // Current cooldown timer
    const float ATTACK_COOLDOWN_TIME = 1.0f; // Time between attacks
    bool isAggressive = true;                // Whether NPC will chase/attack player

private:
    std::unordered_map<State, Spritesheet*> npcAnimations;
    std::vector<Vector2> currentPath;

    Vector2 targetPosition;
    bool inCombat = false;


};
