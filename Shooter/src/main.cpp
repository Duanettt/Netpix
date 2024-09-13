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

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Netpix");

    InitAudioDevice();

    auto& sceneManager = SceneManager::getInstance();

    Player player;

    Spritesheet* idleSpritesheet = new IdleSpritesheet("res/character/npc1/Idle.png");
    Spritesheet* walkingSpritesheet = new WalkingSpritesheet("res/character/npc1/Walk.png");

    std::unordered_map<State, Spritesheet*> spritesheets = {
        {IDLE, idleSpritesheet},
        {WALKING, walkingSpritesheet} 
    };

    auto npc = std::make_unique<NPC>(spritesheets);

    SceneBuilder builder;
    builder.AddComponent(std::make_unique<Background>("res/background/b1/1.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b1/2.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b1/3.png"))
        .AddComponent(std::make_unique<Foreground>("res/background/b1/4.png"));

    Scene scene = builder.Build();

    builder.AddComponent(std::make_unique<Foreground>("res/background/b2/1.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b2/2.png"))
        .AddComponent(std::make_unique<Midground>("res/background/b2/3.png"))
        .AddComponent(std::make_unique<Background>("res/background/b2/4.png"))
        .AddObject(std::make_unique<NPC>(spritesheets))
        .AddMusic("music1", std::make_unique<MusicComponent>("res/sounds/CVHarris.mp3"));


    Scene scene2 = builder.Build();


    sceneManager.AddScene(&scene)
                .AddScene(&scene2);

    npc->setCurrentAnimation(WALKING);
    scene2.getNPC()->setCurrentAnimation(IDLE);

    sceneManager.SetScene(1);
    GameScreen gs = LOGO;
    
    CameraController camera;
         
   // Music music = LoadMusicStream("src/sounds/CVHarris.mp3");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) 
    {
        //UpdateMusicStream(music);
        

        //PlayMusicStream(music);

        sceneManager.getCurrentScene()->setCurrentSong("music1");

        sceneManager.UpdateCurrentScene(player, camera);

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));


        sceneManager.DrawCurrentScene(player, camera);

        DrawText("use WASD to move", 10, 10, 20, RED);
        DrawText("(c) Netpix by Duaine Nettey", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    builder.Unload();

    return 0;
} 