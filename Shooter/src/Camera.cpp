#include "Camera.h"


void CameraController::UpdateCamera(const Vector2& playerPosition, float worldWidth, float worldHeight)
{
	// Initially set the camera to our players position.
	camera.target = playerPosition;
	// Calculate half of the screenWidth for our boundary checks.
	float halfScreenWidth = GetScreenWidth() / 2;
	float halfScreenHeight = GetScreenHeight() / 2;

	// Do boundary checks.
	XAxisBoundaryCheck(playerPosition, halfScreenWidth, worldWidth);
	YAxisBoundaryCheck(playerPosition, halfScreenHeight, worldHeight);

}

void CameraController::BeginCameraMode()
{
	BeginMode2D(camera);
}

void CameraController::EndCameraMode()
{
	EndMode2D();
}

// Getters and Setters
void CameraController::setCameraTargetX(float cameraTarget)
{
	camera.target.x = cameraTarget;
}

void CameraController::setCameraTargetY(float cameraTarget)
{
	camera.target.y = cameraTarget;
}

Vector2 CameraController::getCameraOffset()
{
	return { camera.target.x - camera.offset.x, 0.0f }; // Ignore vertical offset
}


Vector2 CameraController::getCameraPosition()
{
	return camera.target;
}

void CameraController::XAxisBoundaryCheck(const Vector2& playerPosition, float halfScreenWidth, float worldWidth)
{

	if (playerPosition.x - halfScreenWidth <= 0)
	{
		camera.target.x = halfScreenWidth;
	}
	else if (playerPosition.x + halfScreenWidth >= worldWidth)
	{
		camera.target.x = worldWidth - halfScreenWidth;
	}
	else
	{
		camera.target = playerPosition;
	}

}

void CameraController::YAxisBoundaryCheck(const Vector2& playerPosition, float halfScreenHeight, float worldHeight)
{
	if (playerPosition.y - halfScreenHeight <= 190)
	{
		camera.target.y = halfScreenHeight;
	}
	else if (playerPosition.y + halfScreenHeight >= worldHeight)
	{
		camera.target.y = worldHeight - halfScreenHeight;
	}
	else
	{
		camera.target = playerPosition;
	}
}

