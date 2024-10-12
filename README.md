# Netpix
![image](https://github.com/user-attachments/assets/104dabab-e34c-49a4-9b37-0e14c513b539)
**Netpix** is a 2D game/game engine developed in C++ using the Raylib library. This project serves as a platform to deepen my knowledge of C++ and game development concepts, from basic rendering to more advanced features like scene management and sprite-based animations.

## Features

- 2D Game World: Navigate through various scenes with background, midground, and foreground elements.
- Player Movement: Movement mechanics allow players to move left and right, with support for animations based on the player's state (e.g., running, idle).
- Animation System: Support for loading and managing animations from spritesheets, including attack, idle, walking, and running animations.
- Parallax Scrolling: The background moves based on the player's movement, creating a sense of depth.
- Sound & Music Integration: In-game music is managed using a MusicComponent system to provide a dynamic audio experience.

## How to Use

As of September 2024, **Netpix** is primarily set up for use with **Visual Studio**. I am actively working on adding **CMake** support to make the project more versatile across platforms and development environments.

### Running the Project

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/netpix.git
   ```

2. **Open in Visual Studio:**
   * Open the `solution.sln` file in Visual Studio.

3. **Build and Run:**
   * Select your configuration (e.g., `x64/Debug`) and build the project.
   * Run the game directly from Visual Studio.

I will update this section with CMake instructions once it's ready for cross-platform development.

## Usages
- Movement: Control the player using the arrow keys.
- Animations: Player states change automatically based on movement and interactions.
- Music: Background music plays while the game runs. You can customize it by replacing the audio files in the assets directory.

## Future Plans
- Combat System: Implement a combat system allowing players to attack enemies and NPC's, this mainly involves building out our collision detection.
- Level System: Add multiple levels with increasing difficulty.
- Menu System: Implement a main menu and pause menu with options for controlling music and game settings.
- NPC AI System: Learning A* for AI development,
