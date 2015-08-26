#include "Errors.h"

#include <exception>

#include "Log.h"

class FailureException : public std::exception
{
};

void MySDL_Error(const std::string& message)
{
	LOG_STREAM(std::cerr) << message << " error: " << SDL_GetError();
	SDL_Quit();
	std::cin.ignore();
	throw FailureException();
}

void printCoord(int x, int y)
{
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}