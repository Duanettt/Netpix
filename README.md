# Netpix
**Netpix** is a 2D game/game engine developed in C++ using the Raylib library. This project serves as a platform to deepen my knowledge of C++ and game development concepts, from basic rendering to more advanced features like scene management and sprite-based animations.

![Newnetpixrecording-ezgif com-optimize](https://github.com/user-attachments/assets/ce9bf446-c855-4279-81ed-c87f4f9369ba)

## Features

- 2D Game World: Navigate through various scenes with background, midground, and foreground elements.
- Player Movement: Movement mechanics allow players to move left and right, with support for animations based on the player's state (e.g., running, idle).
- Animation System: Support for loading and managing animations from spritesheets, including attack, idle, walking, and running animations.
- Parallax Scrolling: The background moves based on the player's movement, creating a sense of depth.
- Sound & Music Integration: In-game music is managed using a MusicComponent system to provide a dynamic audio experience.

## How to Use

As of September 2024, **Netpix** is primarily set up for use with **Visual Studio**. I am actively working on adding **CMake** support to make the project more versatile across platforms and development environments.

### Running the Project

**With CMake**
_______

1. Before, install in specifically vcpkg raylib e.g
   * ./vcpkg install raylib
   * ./vcpkg integrate install
2. Clone the Repository and run the command "cd Shooter"
3. Then run this command:
   * cmake -DCMAKE_TOOLCHAIN_FILE=C:/vcpkg/scripts/buildsystems/vcpkg.cmake -DCMAKE_PREFIX_PATH="C:/vcpkg/installed/x64-windows/share/raylib" ..
   * cmake --build .
4. Then cd BuildMode(e.g. Debug) and then run Netpix.exe


**In Visual Studio**
_______

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/netpix.git
   ```

2. **Open in Visual Studio:**
   * Open the `solution.sln` file in Visual Studio.
  
3. Within the **ResourceManager.h** file, for now, you'll need to change the resourcePath variable to "./res" instead of the "../res/" due to how the relative paths are working for this code base.

4. **Build and Run:**
   * Select your configuration (e.g., `x64/Debug`) and build the project.
   * Run the game directly from Visual Studio.

I will update this section with CMake instructions once it's ready for cross-platform development.

## Usages
- Movement: Control the player using the arrow keys.
- Animations: Player states change automatically based on movement and interactions.
- Music: Background music plays while the game runs. You can customize it by replacing the audio files in the assets directory.

## Future Plans
- Resource Manager: Implement a resource manager to load all my textures, spritesheets etcetera. [COMPLETED]
- Combat System: Implement a combat system allowing players to attack enemies and NPC's, this mainly involves building out our collision detection.
- Level System: Add multiple levels with increasing difficulty.
- Menu System: Implement a main menu and pause menu with options for controlling music and game settings. (50%)
- NPC AI System: Learning A* for AI development,

**Note:** 
- The game is extremely object oriented and after reevaluating and learning more on C++ code design a rebuild may happen. However I will complete this little project and use it as a basis.
