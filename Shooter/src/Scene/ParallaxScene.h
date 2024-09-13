#pragma once
#include <raylib.h>
#include <vector>
#include <string>

class SceneComponent
{
public:
    SceneComponent(const char* filePath)
    {
        tex = LoadTexture(filePath);
        if (tex.width == 0 || tex.height == 0)
        {
            // Handle texture loading error
            TraceLog(LOG_ERROR, "Failed to load texture: %s", filePath);
        }
    }

    SceneComponent() {}

    void Unload()
    {
        UnloadTexture(tex);
    }

    int getWidth() const { return tex.width; }
    int getHeight() const { return tex.height; }
    Texture2D getTex() const 
    {
        return tex; 
    }

private:
    Texture2D tex;
};

class Scene
{
public:
    Scene(const SceneComponent& bg, const SceneComponent& mg, const SceneComponent& fg)
        : background(bg), midground(mg), foreground(fg)
    {
    }

    void UpdateScene()
    {
        scrollingBack -= 0.1f;
        scrollingMid -= 0.5f;
        scrollingFore -= 1.0f;

        if (scrollingBack <= -background.getWidth() * 2) scrollingBack = 0;
        if (scrollingMid <= -midground.getWidth() * 2) scrollingMid = 0;
        if (scrollingFore <= -foreground.getWidth() * 2) scrollingFore = 0;


        player.Update();
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
        DrawTextureEx(background.getTex(), Vector2{scrollingFore, 450.0f - (background.getHeight() * 2)}, 0.0f, 2.0f, WHITE);
        DrawTextureEx(background.getTex(), Vector2{ scrollingFore + background.getWidth() * 2, 450.0f - (background.getHeight() * 2) }, 0.0f, 2.0f, WHITE);


        // Draw middleground twice
        /*
        * The second parameter is a vector, scrolling fore sets the horizontal x value
        * screenHeight - foreground etcetera, this sets the vertical position. This helps to place the texture so that its bottom edge aligns with our window/screen height.
        */
        DrawTextureEx(midground.getTex(), Vector2{ scrollingFore, 450.0f - (midground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(midground.getTex(), Vector2{ scrollingFore + midground.getWidth() * 2, 450.0f - (midground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);



        // Draw foreground image twice
        DrawTextureEx(foreground.getTex(), Vector2{ scrollingFore, 450.0f - (foreground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);
        DrawTextureEx(foreground.getTex(), Vector2{ scrollingFore + foreground.getWidth() * 2, 450.0f - (foreground.getHeight() * 2) }, 0.0f, 2.0f, WHITE);

        player.Draw();
    }

private:
    float scrollingBack = 0.0f;
    float scrollingMid = 0.0f;
    float scrollingFore = 0.0f;

    SceneComponent background;
    SceneComponent midground;
    SceneComponent foreground;
};

class SceneBuilder
{
public:
    SceneBuilder& AddBackground(const char* filePath)
    {
        background = SceneComponent(filePath);
        return *this;
    }

    SceneBuilder& AddMidground(const char* filePath)
    {
        midground = SceneComponent(filePath);
        return *this;
    }

    SceneBuilder& AddForeground(const char* filePath)
    {
        foreground = SceneComponent(filePath);
        return *this;
    }

    Scene Build() const
    {
        return Scene(background, midground, foreground);
    }

    void Unload()
    {
        background.Unload();
        midground.Unload();
        foreground.Unload();
    }
private:
    SceneComponent background;
    SceneComponent midground;
    SceneComponent foreground;
};
