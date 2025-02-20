#include "Camera.h"


void CameraController::UpdateCamera(const Vector2& playerPosition, float worldWidth, float worldHeight) {
	float delta = GetFrameTime();
	float cameraSmoothness = 5.0f; // Adjust this value to change camera smoothing

	Vector2 targetPosition = playerPosition;
	float halfScreenWidth = GetScreenWidth() / 2;
	float halfScreenHeight = GetScreenHeight() / 2;


	// X Axis Boundary checks can put in a function if need be
	if (targetPosition.x - halfScreenWidth <= 0) {
		targetPosition.x = halfScreenWidth;
	}
	else if (targetPosition.x + halfScreenWidth >= worldWidth) {
		targetPosition.x = worldWidth - halfScreenWidth;
	}

	// Y Axis Boundary checks
	if (targetPosition.y - halfScreenHeight <= 190) {
		targetPosition.y = halfScreenHeight;
	}
	else if (targetPosition.y + halfScreenHeight >= worldHeight) {
		targetPosition.y = worldHeight - halfScreenHeight;
	}

	// Linear interpolation but chase method instead. Where camera.target.x = start, the targetPosition.x - cameraTarget = to the end and we then interpolate across using cameraSmoothness * delta which basically gives us a fraction in which how far
	// The camera is in terms of our player.
	camera.target.x = camera.target.x + (targetPosition.x - camera.target.x) * cameraSmoothness * delta;
	camera.target.y = camera.target.y + (targetPosition.y - camera.target.y) * cameraSmoothness * delta;
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

bool CameraController::getCameraDirection(float objectPosition)
{
	{
		float currentOffset = this->getCameraOffset().x;
		float currentPosition = this->getCameraPosition().x;

		if (currentPosition + currentOffset >= objectPosition)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}
