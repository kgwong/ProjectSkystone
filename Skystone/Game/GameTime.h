#ifndef TIME_H
#define TIME_H

#include <SDL/SDL.h>

class Time
{
public:
	static const int timeStep = 20;

	static uint32_t getCurrentTime();
	static uint32_t getElapsedUpdateTime();
	static uint32_t getElapsedRenderTime();
	static void setElapsedRenderTime(uint32_t time);
private:
	Time()  = delete;
	~Time() = delete;

	static uint32_t lastRender_;
	
};

#endif //TIME_H
