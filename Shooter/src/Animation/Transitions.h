#pragma once
#include <functional>
#include <raylib.h>

class Transitions
{
public:
	Transitions();
	Transitions(float duration);
	void Start();
	virtual void Update(float deltaTime) = 0;
	float GetProgress();
	bool isActive();

	float elapsedTime = 0.0f;
	float transitionDuration;
private:
	bool active = false;
};


class FadeInTransition : public Transitions
{
public:
	FadeInTransition(float fadeDuration, Color color);

	void Update(float deltaTime);

	Color fadeColor;
private:
};
