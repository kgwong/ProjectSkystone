#include "Time.h"

uint32_t Time::lastUpdate_{SDL_GetTicks()};
uint32_t Time::lastRender_{SDL_GetTicks()};

uint32_t Time::getCurrentTime()
{
	return SDL_GetTicks();
}

uint32_t Time::getElapsedUpdateTime()
{
	uint32_t current = Time::getCurrentTime();
	uint32_t elapsed = current - lastUpdate_;
	lastUpdate_ = current;
	return elapsed;
}

uint32_t Time::getElapsedRenderTime()
{

	uint32_t current = Time::getCurrentTime();
	uint32_t elapsed = current - lastRender_;
	lastRender_ = current;
	return elapsed;
}