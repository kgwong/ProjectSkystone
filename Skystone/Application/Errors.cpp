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

SDL_Window* MySDL_CreateWindow(const char* title,
								int x, int y, int w,
								int h, Uint32 flags)
{
	SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, flags);
	if (!window)
	{
		MySDL_Error("SDL_CreateWindow");
	}
	return window;
}

SDL_Renderer* MySDL_CreateRenderer(SDL_Window* window,
									int index, Uint32 flags)
{
	SDL_Renderer* renderer = SDL_CreateRenderer(window, index, flags);
	if (!renderer)
	{
		SDL_DestroyWindow(window);
		MySDL_Error("SDL_CreateRenderer");
	}
	return renderer;
}

void MySDL_RenderCopy(SDL_Renderer* renderer,
						SDL_Texture* texture,
						const SDL_Rect* srcrect,
						const SDL_Rect* dstrect)
{
	if (SDL_RenderCopy(renderer, texture, srcrect, dstrect) == -1)
		LOG_STREAM(std::cerr) << "SDL_RenderCopy: " << SDL_GetError();
}


void printCoord(int x, int y)
{
	std::cout << "(" << x << ", " << y << ")" << std::endl;
}