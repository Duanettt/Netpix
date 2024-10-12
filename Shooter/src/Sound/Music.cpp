#include "Music.h"

// Constructor to load music from a file path.
MusicComponent::MusicComponent(const char* filePath)
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

// Destructor to unload the music stream.
MusicComponent::~MusicComponent()
{
    UnloadMusicStream(music);
}

// Play the loaded music.
void MusicComponent::PlayMusic()
{
    if (music.frameCount > 0)
    {
        PlayMusicStream(music);
    }
}

// Update the music stream.
void MusicComponent::UpdateMusic()
{
    if (music.frameCount > 0)
    {
        UpdateMusicStream(music);
    }
}

// Check if the music component is valid.
bool MusicComponent::IsValid() const
{
    return music.frameCount > 0;
}
