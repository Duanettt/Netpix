#pragma once
#include <raylib.h>

// MusicComponent handles loading, playing, and updating music streams.
class MusicComponent
{
public:
    // Constructor to load music from a file path.
    MusicComponent(const char* filePath);

    // Destructor to unload the music stream.
    ~MusicComponent();

    // Play the loaded music.
    void PlayMusic();

    // Update the music stream.
    void UpdateMusic();

    // Check if the music component is valid.
    bool IsValid() const;

private:
    Music music;
};