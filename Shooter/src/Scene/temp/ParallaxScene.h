#pragma once
#include <raylib.h>
#include <vector>
#include <string>
#include "../SceneManager.h"

// This is a junk class to be honest will find a way to create a parallax background with the scene class rather than calling this class object.
class ParallaxScene
{
public:
    ParallaxScene(const char* backgroundTextureKey)
    {
        background = ResourceManager::getInstance().GetResource<Texture2D>(backgroundTextureKey);
    }

    ParallaxScene()
    {

    }

    void UpdateScene()
    {
        scrollingBack -= 0.4f;
        //scrollingMid -= 0.5f;
        //scrollingFore -= 1.0f;

        if (scrollingBack <= -background.width * 2) scrollingBack = 0;


    }

    void DrawScene() const
    {
        // Draw background twice
        /*
        * We draw the texture twice to create the illusion of an infinitely scrolling foreground.
        * The first texture is drawn at its current scrolling point, the second one is drawn immediately after the first texture ends.
        * First draw call places the first foreground texture at the scrolling position
        * We place a second copy of the foreground texture right after the first one, at scrollingFore + foreground.width * 2. The foreground.width * 2 accounts for the width of the texture, considering that it's scaled by a factor of 2.0. By placing the second texture here, it "follows" the first one and will appear when the first texture has moved off the screen
        */
        DrawTextureEx(background, Vector2{ scrollingBack, 450.0f - (background.height * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background, Vector2{ scrollingBack + background.width * 2, 450.0f - (background.height * 2) }, 0.0f, 2.0f, WHITE);


        // Draw middleground twice
        /*
        * The second parameter is a vector, scrolling fore sets the horizontal x value
        * screenHeight - foreground etcetera, this sets the vertical position. This helps to place the texture so that its bottom edge aligns with our window/screen height.
        */
        //DrawTextureEx(midground.getTex(), Vector2{ scrollingFore, 450.0f - (midground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);
        //DrawTextureEx(midground.getTex(), Vector2{ scrollingFore + midground.getWidth() * 2, 450.0f - (midground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);



        // Draw foreground image twice
 /*       DrawTextureEx(foreground.getTex(), Vector2{ scrollingFore, 450.0f - (foreground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreground.getTex(), Vector2{ scrollingFore + foreground.getWidth() * 2, 450.0f - (foreground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);*/

    }

private:
    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    Texture2D background;
};

//class SceneBuilder
//{
//public:
//    SceneBuilder& AddBackground(const char* filePath)
//    {
//        background = ParallaxSceneComponent(filePath);
//        return *this;
//    }
//
//    SceneBuilder& AddMidground(const char* filePath)
//    {
//        midground = ParallaxSceneComponent(filePath);
//        return *this;
//    }
//
//    SceneBuilder& AddForeground(const char* filePath)
//    {
//        foreground = ParallaxSceneComponent(filePath);
//        return *this;
//    }
//
//    ParallaxScene Build() const
//    {
//        return ParallaxScene(background, midground, foreground);
//    }
//
//    void Unload()
//    {
//        background.Unload();
//        midground.Unload();
//        foreground.Unload();
//    }
//private:
//    ParallaxSceneComponent background;
//    ParallaxSceneComponent midground;
//    ParallaxSceneComponent foreground;
//};