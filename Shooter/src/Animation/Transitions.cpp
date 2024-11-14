#include "Transitions.h"

Transitions::Transitions()
{
}


// We create a transition object which has a duration and a function with this transition object to callback when needed.
Transitions::Transitions(float duration) : transitionDuration(duration)
{

}

void Transitions::Start()
{
	elapsedTime = 0.0f;
	active = true;
}

void Transitions::Update(float deltaTime)
{
	if (active)
	{
		elapsedTime += deltaTime;

		if (elapsedTime > transitionDuration)
		{
			elapsedTime = deltaTime;
			active = false;
		}
	}
}

float Transitions::GetProgress()
{
	return (elapsedTime / transitionDuration);
}

bool Transitions::isActive()
{
	return active;
}

FadeInTransition::FadeInTransition(float fadeDuration, Color color) : Transitions(fadeDuration), fadeColor(color)
{

}

void FadeInTransition::Update(float deltaTime)
{
	if (this->isActive())
	{
		elapsedTime += deltaTime;

		float alpha = 0.0f;
		
		if (elapsedTime > transitionDuration)
		{
			
		}
	}
}
