#pragma once

enum State {
    IDLE = 0,
    WALKING = 1,
    RUNNING = 2,
    JUMPING = 3,
    ATTACK = 4,
};

enum MouseStates
{
    NORMAL = 0,
    MOUSE_HOVER = 1,
    PRESSED = 2,
};

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

// For the attack state we can use a progress animation checker. We can check the progress of the animation each time the animation is called. 