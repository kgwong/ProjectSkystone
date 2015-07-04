#include "GameWindow.h"

GameWindow::GameWindow(std::string windowName, int width, int height)
	:_width(width), _height(height)
{
	window = SDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

	if (window == nullptr)
		MySDL_Error("SDL_CreateWindow");

	
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == nullptr)
	{
		SDL_DestroyWindow(window);
		MySDL_Error("SDL_CreateRenderer");
	}

	camera.setWidth(width);
	camera.setHeight(height);

}

GameWindow::~GameWindow()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
}

int GameWindow::getWidth() const
{
	return _width;
}

int GameWindow::getHeight() const
{
	return _height;	
}


