#include "raylib.h"

#include <memory>

#include "../src/Core/ScreenManager.h"
#include "../src/Core/States.h"
#include "../src/Scene/Scene.h"
#include "../src/Animation/Animation.h"
#include "../src/Core/Camera.h"
#include "../src/Scene/SceneManager.h"


#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1


// New idea: When loading scene if we have npc's we can have an array of pointers to npc objects and clear each time a scene is over then add 
// the npc objects to vector and draw whenevers theres a new scene.
// We'll utilise the scene builder for this aswell.

typedef enum GameScreen { LOGO = 0, TITLE, GAMEPLAY, ENDING } GameScreen;

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Netpix");

    InitAudioDevice();

    auto& sceneManager = SceneManager::getInstance();

    Player player;

    // Solve collision detection problems..

    Spritesheet* idleSpritesheet = new IdleSpritesheet("res/character/npc1/Idle.png",6);
    Spritesheet* walkingSpritesheet = new WalkingSpritesheet("res/character/npc1/Walk.png",10);

    std::unordered_map<State, Spritesheet*> spritesheets = {
        {IDLE, idleSpritesheet},
        {WALKING, walkingSpritesheet} 
    };


 /*   Spritesheet* tracyIdleSpritesheet = new IdleSpritesheet("res/character/Onre/Idle.png", 6);
    Spritesheet* tracyWalkingSpritesheet = new WalkingSpritesheet("res/character/Onre/Run.png", 10);


    std::unordered_map<State, Spritesheet*> tSpritesheets = {
       {IDLE, tracyIdleSpritesheet},
       {WALKING, tracyWalkingSpritesheet}
    };  */

    SceneBuilder builder;
    //ScreenManager screenManager;

    builder.AddComponent(std::make_unique<Background>("res/background/b1/1.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b1/2.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b1/3.png"))
        .AddComponent(std::make_unique<Foreground>("res/background/b1/4.png"))
        .AddObject(std::make_unique<NPC>(spritesheets))
        .AddMusic("music1", std::make_unique<MusicComponent>("res/sounds/CVHarris.mp3"));

    Scene scene1 = builder.Build();

    builder.AddComponent(std::make_unique<Foreground>("res/background/b2/1.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b2/2.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b2/3.png"))
        .AddComponent(std::make_unique<Background>("res/background/b2/4.png"))
        .AddObject(std::make_unique<NPC>(spritesheets))
        .AddMusic("music2", std::make_unique<MusicComponent>("res/sounds/Tems-FreeMind.mp3"));

    Scene scene2 = builder.Build();

    sceneManager.AddScene(std::make_unique<Scene>(scene2));
    sceneManager.AddScene(std::make_unique<Scene>(scene1));


    //sceneManager.SetScene(1);

    //sceneManager.getCurrentScene()->setCurrentSong("music2");

    //sceneManager.getCurrentScene()->getNPCByIndex(0)->setCurrentAnimation(IDLE);

    // Bug 1 -> When we set the position it doesn't update the draw object position.
    //sceneManager.getCurrentScene()->getNPCByIndex(0)->setPosition({ 450, 250 });

    CameraController camera;

    GameScreen currentScreen = GameScreen::LOGO;


    int mainFramesCounter = 0;
   // Music music = LoadMusicStream("src/sounds/CVHarris.mp3");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) 
    {
        // Will be placing all of this in its own function soon.
        switch (currentScreen)
        {
            case GameScreen::LOGO:

                mainFramesCounter++;
                sceneManager.SetScene(2);
                sceneManager.getCurrentScene()->setCurrentSong("music1");




                std::cout << mainFramesCounter << std::endl;

                sceneManager.UpdateCurrentScene(player, camera);

                if (mainFramesCounter > 120)
                {
                    currentScreen = GameScreen::GAMEPLAY;
                }
                
                break;

            case GameScreen::GAMEPLAY:

                sceneManager.SetScene(1);
                sceneManager.getCurrentScene()->setCurrentSong("music2");

                sceneManager.UpdateCurrentScene(player, camera);       

                break;
        }

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));

        switch (currentScreen)
        {
            case GameScreen::LOGO:
            {
            // TODO: Draw LOGO screen here!
            /*DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);*/

                sceneManager.DrawCurrentScene(player, camera);
            break;
            };
            case GameScreen::GAMEPLAY:
            {
                // TODO: Draw GAMEPLAY screen here!
                sceneManager.DrawCurrentScene(player, camera);
                break;
            }        
        }

        //sceneManager.UpdateCurrentScene(player, camera);

        //BeginDrawing();
        //ClearBackground(GetColor(0x052c46ff));

        //sceneManager.DrawCurrentScene(player, camera);

        //DrawText("use WASD to move", 10, 10, 20, RED);
        //DrawText("(c) Netpix by Duaine Nettey", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    builder.Unload();

    return 0;
} 