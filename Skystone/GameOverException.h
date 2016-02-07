#ifndef GAME_OVER_EXCEPTION_H
#define GAME_OVER_EXCEPTION_H

#include <exception>

//TEMPORARY

class GameOverException :
	public std::exception
{
public:
	GameOverException();
	~GameOverException();
};

#endif //GAME_OVER_EXCEPTION_H