#include "Time.h"

uint32_t Time::lastUpdate_{SDL_GetTicks()};
uint32_t Time::lastRender_{SDL_GetTicks()};

uint32_t Time::getCurrentTime()
{
	return SDL_GetTicks();
}

uint32_t Time::getElapsedUpdateTime()
{
	return Time::getCurrentTime() - lastUpdate_;
}

uint32_t Time::getElapsedRenderTime()
{
	return Time::getCurrentTime() - lastRender_;
}

void Time::updateLastUpdateTime()
{
	lastUpdate_ = Time::getCurrentTime();
}

void Time::updateLastRenderTime()
{
	lastRender_ = Time::getCurrentTime();
}