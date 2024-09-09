#include "ScreenManager.h"


void ScreenManager::UpdateScreen(GameScreen& currentScreen, int& framesCounter, Player& player)
{
    switch (currentScreen)
    {
    case LOGO:
    {
        // TODO: Update LOGO screen variables here!

        framesCounter++;    // Count frames

        // Wait for 2 seconds (120 frames) before jumping to TITLE screen
        if (framesCounter > 120)
        {
            currentScreen = TITLE;
        }
    } break;
    case TITLE:
    {
        // TODO: Update TITLE screen variables here!

        // Press enter to change to GAMEPLAY screen
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            currentScreen = GAMEPLAY;
        }
    } break;
    case GAMEPLAY:
    {
        // TODO: Update GAMEPLAY screen variables here!
        player.Update();

        // Press enter to change to ENDING screen
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            currentScreen = ENDING;
        }
    } break;
    case ENDING:
    {
        // TODO: Update ENDING screen variables here!

        // Press enter to return to TITLE screen
        if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
        {
            currentScreen = TITLE;
        }
    } break;
    default: break;
    }
}

void ScreenManager::DrawScreen(GameScreen& currentScreen, int screenWidth, int screenHeight, Player& player)
{
    switch (currentScreen)
    {
    case LOGO:
    {
        // TODO: Draw LOGO screen here!
        DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
        DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);

    } break;
    case TITLE:
    {
        // TODO: Draw TITLE screen here!
        DrawRectangle(0, 0, screenWidth, screenHeight, GREEN);
        DrawText("TITLE SCREEN", 20, 20, 40, DARKGREEN);
        DrawText("PRESS ENTER or TAP to JUMP to GAMEPLAY SCREEN", 120, 220, 20, DARKGREEN);


    } break;
    case GAMEPLAY:
    {
        // TODO: Draw GAMEPLAY screen here!
        DrawRectangle(0, 0, screenWidth, screenHeight, PURPLE);
        DrawText("GAMEPLAY SCREEN", 20, 20, 40, MAROON);
        DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);

        player.Draw();

    } break;
    case ENDING:
    {
        // TODO: Draw ENDING screen here!
        DrawRectangle(0, 0, screenWidth, screenHeight, BLUE);
        DrawText("ENDING SCREEN", 20, 20, 40, DARKBLUE);
        DrawText("PRESS ENTER or TAP to RETURN to TITLE SCREEN", 120, 220, 20, DARKBLUE);

    } break;
    default: break;
    }
}


