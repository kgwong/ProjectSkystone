#include "GameTime.h"

uint32_t Time::lastRender_{SDL_GetTicks()};

uint32_t Time::getCurrentTime()
{
	return SDL_GetTicks();
}

uint32_t Time::getElapsedUpdateTime()
{
	return Time::timeStep;
}

float Time::getElapsedUpdateTimeSeconds()
{
	return Time::timeStep / 1000.0f;
}

uint32_t Time::getElapsedRenderTime()
{
	return lastRender_;
}

void Time::setElapsedRenderTime(uint32_t time)
{
	lastRender_ = time;
}