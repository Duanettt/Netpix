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
        if (music.frameCount > 0) {
            PlayMusicStream(music);
        }
        else {
        }
    }

    void UpdateMusic()
    {

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