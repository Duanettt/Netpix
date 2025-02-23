#include "raylib.h"

#include <memory>

#include "../src/Core/ScreenManager.h"
#include "../src/ResourceManager.h"
#include "../src/Core/States.h"
#include "../src/Scene/Scene.h"
#include "../src/Animation/Animation.h"
#include "../src/Core/Camera.h"
#include "../src/Scene/SceneManager.h"
#include "../src/UI/GUI.h"
#include "Game/InventorySystem.h"


#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1


// New idea: When loading scene if we have npc's we can have an array of pointers to npc objects and clear each time a scene is over then add 
// the npc objects to vector and draw whenevers theres a new scene.
// We'll utilise the scene builder for this aswell.


int main(void) {
    // Figuring out how to make the game look better in full screen is also another thing on the list to check for.
    const int screenWidth = 800;
    const int screenHeight = 450;


    InitWindow(screenWidth, screenHeight, "Netpix");

    InitAudioDevice();


    ResourceManager& rm = ResourceManager::getInstance();
    auto& sceneManager = SceneManager::getInstance();
    // Might make dialogueManager a s

    Player player;

    // Solve collision detection problems..

    Spritesheet* idleSpritesheet = new IdleSpritesheet(std::string("npc1_4"), 6);
    Spritesheet* walkingSpritesheet = new WalkingSpritesheet(std::string("npc1_6"), 10);
    Spritesheet* runningSpritesheet = new RunningSpritesheet(std::string("npc1_5"), 10);

    std::unordered_map<State, Spritesheet*> spritesheets = {
        {IDLE, idleSpritesheet},
        {WALKING, walkingSpritesheet}, 
        {RUNNING, runningSpritesheet},
    };


    Spritesheet* tracyIdleSpritesheet = new IdleSpritesheet(std::string("Onre_7"), 6);
    Spritesheet* tracyWalkingSpritesheet = new WalkingSpritesheet(std::string("Onre_10"), 7);
    Spritesheet* tracyRunningSpritesheet = new RunningSpritesheet(std::string("Onre_8"), 7);

    std::unordered_map<State, Spritesheet*> tSpritesheets = {
       {IDLE, tracyIdleSpritesheet},
       {WALKING, tracyWalkingSpritesheet},
       {RUNNING, tracyRunningSpritesheet}
    };  

    SceneBuilder builder;
    // FIXME: Stop using so much std::strings performance issue switch to const char* soon.camera.target.x = worldWidth - halfScreenWidth;
    // FIXME: I really have to fix the whole npcs in other scenes.. (FIXED i think!)
    builder.AddComponent(std::make_unique<Background>(std::string("b1_1")))
        .AddComponent(std::make_unique<Midground>(std::string("b1_2")))
        .AddComponent(std::make_unique<Midground>(std::string("b1_3")))
        .AddComponent(std::make_unique<Foreground>(std::string("b1_4")))
        .AddObject(std::make_unique<NPC>(tSpritesheets))
        .AddMusic("music1", std::make_unique<MusicComponent>("game_music_1"));

    Scene scene1 = builder.Build();

    builder.AddComponent(std::make_unique<Background>(std::string("b2_1")))
        .AddComponent(std::make_unique<Midground>(std::string("b2_2")))
        .AddComponent(std::make_unique<Midground>(std::string("b2_3")))
        .AddComponent(std::make_unique<Foreground>(std::string("b2_4")))
        .AddObject(std::make_unique<NPC>(spritesheets))
        .AddObject(std::make_unique<NPC>(tSpritesheets))
        .AddMusic("music2", std::make_unique<MusicComponent>("game_music_3"));

    Scene scene2 = builder.Build();

    sceneManager.AddScene(std::make_unique<Scene>(scene2));
    sceneManager.AddScene(std::make_unique<Scene>(scene1));

    sceneManager.SetScene(1);

   

    // One thing since we're returning like references in our resource manager it will play music at the last point it was played at so.. maybe a fix will be needed.
    //sceneManager.getCurrentScene()->setCurrentSong("music2");

    sceneManager.getCurrentScene()->getNPCByIndex(0)->setPosition({ 758, 200 });
    sceneManager.getCurrentScene()->getNPCByIndex(1)->setPosition({ 458, 200 });

    sceneManager.getCurrentScene()->InitNavGraph();


    CameraController camera;

    GameScreen currentScreen = GameScreen::LOGO;
    
    Vector2 mousePoint = { 0.0f , 0.0f };

    Menu menu;

    NPC* npc = sceneManager.getCurrentScene()->getNPCByIndex(0);

    // The reason for one of these bugs is because basically in our scene builder we have a vector full of objects we're adding and when we build one scene the settings are saved due to the vector stored.. 
    // Once one scene is done we basically need to unload these vectors and build the next scene thats proving difficult since we woulld need to use unique pointers to transfer ownership from one class to another class. SceneBuilder -> Scene.


    //InventorySystem is;

    //// Create inventory
    //InventorySystem inventory(20); // max 20 items

    //// Register an item type
    //auto swordObject = std::make_shared<GameObjects>(); // Your game object setup here

    //inventory.RegisterItem("sword", swordObject);

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
                //sceneManager.SetScene(2);
                //sceneManager.getCurrentScene()->setCurrentSong("music1");
                mousePoint = GetMousePosition();

              /*  button.Update(mousePoint)*/;
                std::cout << mainFramesCounter << std::endl;

                //sceneManager.UpdateCurrentScene(player, camera);

                if (mainFramesCounter > 120)
                {

                    currentScreen = GameScreen::TITLE;
                }
                
                break;

            case GameScreen::TITLE:
                // We send in the current screen to our menu which will then based on options selected will change our currentScreen variable.
                menu.Update(currentScreen);

                break;

            case GameScreen::GAMEPLAY:

                if (IsKeyPressed(KEY_G)) {  // Or whatever key you prefer
                    sceneManager.getCurrentScene()->ToggleNavGraph();
                }

                std::cout << player.GetPlayerPosition().x << std::endl;
                sceneManager.UpdateCurrentScene(player, camera);       

                break;
        }

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));

        switch (currentScreen)
        {
            case GameScreen::LOGO:
            // TODO: Draw LOGO screen here!
            /*DrawText("LOGO SCREEN", 20, 20, 40, LIGHTGRAY);
            DrawText("WAIT for 2 SECONDS...", 290, 220, 20, GRAY);*/
            //button.Draw();
            //sceneManager.DrawCurrentScene(player, camera);
            break;
            
            case GameScreen::TITLE:
                menu.Draw();

                break;
           
            case GameScreen::GAMEPLAY:
                // TODO: Draw GAMEPLAY screen here!

                sceneManager.DrawCurrentScene(player, camera);
                break;        
        }

        //sceneManager.UpdateCurrentScene(player, camera);

        //BeginDrawing();
        //ClearBackground(GetColor(0x052c46ff));

        //sceneManager.DrawCurrentScene(player, camera);

        DrawFPS(0, 0);
        //DrawText("(c) Netpix by Duaine Nettey", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    builder.Unload();

    return 0;
} 