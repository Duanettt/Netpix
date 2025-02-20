#pragma once
#include <raylib.h>
#include <cmath>
#include <iostream>

class CameraController
{
public:
    CameraController()
    {
        camera.target = { 0.0f, 0.0f };
        camera.offset = { 350.0f, 225.0f };
        camera.rotation = 0.0f;
        camera.zoom = 1.0f;
    }

    // Update camera is responsible for providing real time updates to our cameras position based on the players input.
    // The function performs boundary checks and could become useful for cutscenes we'll see.
    void UpdateCamera(const Vector2& playerPosition, float worldWidth, float worldHeight);
    // Begin camera mode is useful for starting our camera in a specific mode (in our case 2D)
    void BeginCameraMode();
    // End camera mode just stops the camera mode being enabled
    void EndCameraMode();
    // Sets what the cameras looking at relative to the x axis.
    void setCameraTargetX(float cameraTarget);
    // Sets what the cameras looking at relative to the x axis.
    void setCameraTargetY(float cameraTarget);
    // Our getters for getting the camera offset which is how much the camera's moved in relation to the players inputs.
    Vector2 getCameraOffset();
    // Gets the current target of the camera.
    Vector2 getCameraPosition();

    bool getCameraDirection(float objectPosition);

private:
    // Need a camera to utilise so declaration of a camera member variable.
    Camera2D camera;
    float previousOffset = 0.0f;
    float cameraSmoothness = 0.0f;
};