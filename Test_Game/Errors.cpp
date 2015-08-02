#include "Errors.h"
#include <exception>

class FailureException : public std::exception
{
};

void MySDL_Error(std::ostream &os, const std::string& message)
{
	os << message << " error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	std::cin.ignore();
	throw FailureException();
}

void MySDL_Error(const std::string& message)
{
	std::cout << message << " error: " << SDL_GetError() << std::endl;
	SDL_Quit();
	std::cin.ignore();
	throw FailureException();
}

void printCoord(int x, int y)
{
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}