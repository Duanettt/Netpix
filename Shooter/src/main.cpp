#include "raylib.h"

#include <memory>

#include "ScreenManager.h"
#include "NewScene.h"
#include "Camera.h"


#define MAX_FRAME_SPEED     15
#define MIN_FRAME_SPEED      1

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

    SceneBuilder builder;
    builder.AddComponent(std::make_unique<Background>("src/background/b1/1.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b1/2.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b1/3.png"))
        .AddComponent(std::make_unique<Foreground>("src/background/b1/4.png"));


    Scene scene = builder.Build();

    builder.AddComponent(std::make_unique<Foreground>("src/background/b2/1.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b2/2.png"))
        .AddComponent(std::make_unique<Midground>("src/background/b2/3.png"))
        .AddComponent(std::make_unique<Background>("src/background/b2/4.png"));

    Scene scene2 = builder.Build();


    GameScreen gs = LOGO;
    
    CameraController camera;
         
   // Music music = LoadMusicStream("src/sounds/CVHarris.mp3");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    while (!WindowShouldClose()) 
    {
        //UpdateMusicStream(music);
        

        //PlayMusicStream(music);


       /* scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        /*
        * This scrolling fore is used to move the screen leftward.
        scrollingFore -= 1.0f;

        // NOTE: Texture is scaled twice its size, so it sould be considered on scrolling

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.width * 2) scrollingMid = 0;
        if (scrollingFore <= -foreground.width * 2) scrollingFore = 0;
                */

        camera.UpdateCamera(player.GetPlayerPosition());

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