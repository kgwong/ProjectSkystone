#ifndef GAME_OVER_EXCEPTION_H
#define GAME_OVER_EXCEPTION_H

#include <exception>

class GameOverException :
	public std::exception
{
public:
	GameOverException();
	~GameOverException();
};

#endif //GAME_OVER_EXCEPTION_H