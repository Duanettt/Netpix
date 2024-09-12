#include "raylib.h"

#include <memory>

#include "ScreenManager.h"
#include "States.h"
#include "NewScene.h"
#include "Animation.h"
#include "Camera.h"



#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1


// New idea: When loading scene if we have npc's we can have an array of pointers to npc objects and clear each time a scene is over then add 
// the npc objects to vector and draw whenevers theres a new scene.
// We'll utilise the scene builder for this aswell.

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [texture] example - sprite anim");

    InitAudioDevice();

   /**/ Texture2D background = LoadTexture("src/background/b1/1.png");
    Texture2D midground = LoadTexture("src/background/b1/3.png");
    Texture2D foreground = LoadTexture("src/background/b1/4.png");

    //float scrollingBack = 0.0f;
    //float scrollingMid = 0.0f;
    //float scrollingFore = 0.0f;


    Player player;

    Spritesheet* idleSpritesheet = new IdleSpritesheet("src/character/npc1/Idle.png");
    Spritesheet* walkingSpritesheet = new WalkingSpritesheet("src/character/npc1/Walk.png");

    std::unordered_map<State, Spritesheet*> spritesheets = {
        {IDLE, idleSpritesheet},
        {WALKING, walkingSpritesheet} 
    };

    auto npc = std::make_unique<NPC>(spritesheets);

    SceneBuilder builder;
    builder.AddComponent(std::make_unique<Background>("src/background/b1/1.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b1/2.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b1/3.png"))
        .AddComponent(std::make_unique<Foreground>("src/background/b1/4.png"));


    Scene scene = builder.Build();

    builder.AddComponent(std::make_unique<Foreground>("src/background/b2/1.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b2/2.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b2/3.png"))
        .AddComponent(std::make_unique<Background>("src/background/b2/4.png"))
        .AddObject(std::make_unique<NPC>(spritesheets));


    Scene scene2 = builder.Build();


    npc->setCurrentAnimation(WALKING);
    scene2.getNPC()->setCurrentAnimation(IDLE);


    GameScreen gs = LOGO;
    
    CameraController camera;
         
   // Music music = LoadMusicStream("src/sounds/CVHarris.mp3");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) 
    {
        //UpdateMusicStream(music);
        

        //PlayMusicStream(music);

        scene2.UpdateScene(player, camera);

        BeginDrawing();
        ClearBackground(GetColor(0x052c46ff));


        scene2.DrawScene(player, camera);

        DrawText("use WASD to move", 10, 10, 20, RED);
        DrawText("(c) Netpix by Duaine Nettey", screenWidth - 330, screenHeight - 20, 10, RAYWHITE);
        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context
    builder.Unload();

    return 0;
} 