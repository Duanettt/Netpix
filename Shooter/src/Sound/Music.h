class MusicComponent
{
public:
    MusicComponent(const char* filePath)
    {
        music = LoadMusicStream(filePath);
        if (music.frameCount == 0) 
        {
            TraceLog(LOG_ERROR, "Failed to load music: %s", filePath);
        }
        else 
        {
            TraceLog(LOG_INFO, "Successfully loaded music: %s", filePath);
        }
    }

    ~MusicComponent()
    {
        UnloadMusicStream(music);
    }

    void PlayMusic()
    {
        std::cout << "In the play music section" << std::endl;
        if (music.frameCount > 0) {
            PlayMusicStream(music);
            TraceLog(LOG_INFO, "Started playing music");
        }
        else {
            TraceLog(LOG_ERROR, "Attempted to play invalid music");
        }
    }

    void UpdateMusic()
    {
        std::cout << "In the update music section" << std::endl;

        if (music.frameCount > 0) {
            UpdateMusicStream(music);
        }
    }

    bool IsValid() const
    {
        return music.frameCount > 0;
    }

private:
    Music music;
};