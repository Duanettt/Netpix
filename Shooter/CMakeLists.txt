# Set project name
project(Netpix)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add all source files (cpp files) to a variable
set(SOURCES
    src/Animation.cpp
    src/Camera.cpp
    src/GameObjects.cpp
    src/NewScene.cpp
    src/Player.cpp
    src/Scene.cpp
    src/ScreenManager.cpp
    src/main.cpp
)

# Add header files to a variable
set(HEADERS
    src/Animation.h
    src/Camera.h
    src/GameObjects.h
    src/NewScene.h
    src/Player.h
    src/Scene.h
    src/ScreenManager.h
)

# Add raylib (assumed to be installed via vcpkg)
find_package(raylib CONFIG REQUIRED)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link libraries (link raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

# Include directories if needed (for headers)
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Add textures and sprites directory
set(TEXTURE_DIR ${CMAKE_SOURCE_DIR}/src/background)
set(SPRITES_DIR ${CMAKE_SOURCE_DIR}/src/character)

message(STATUS "Texture directory: ${TEXTURE_DIR}")
message(STATUS "Sprites directory: ${SPRITES_DIR}")

# Specify where to copy textures and sprites after the build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${TEXTURE_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/background
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${SPRITES_DIR} $<TARGET_FILE_DIR:${PROJECT_NAME}>/character
)
