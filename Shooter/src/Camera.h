#pragma once
#include <raylib.h>

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


	void UpdateCamera(const Vector2& playerPosition)
	{
		camera.target = playerPosition;
	}

	void BeginCameraMode()
	{
		BeginMode2D(camera);
	}

	void EndCameraMode()
	{
		EndMode2D();
	}

	Vector2 getCameraOffset()
	{
		return { camera.target.x - camera.offset.x, 0.0f }; // Ignore vertical offset
	}

	Vector2 getCameraPosition()
	{
		return camera.target;
	}
private:
	Camera2D camera;
};

