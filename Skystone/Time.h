#ifndef TIME_H
#define TIME_H

#include <SDL/SDL.h>

class Time
{
public:
	static uint32_t getCurrentTime();
	static uint32_t getElapsedUpdateTime();
	static uint32_t getElapsedRenderTime();
	static void updateLastUpdateTime();
	static void updateLastRenderTime();
private:
	Time()  = delete;
	~Time() = delete;

    static uint32_t lastUpdate_;
	static uint32_t lastRender_;
	
};

#endif //TIME_H
