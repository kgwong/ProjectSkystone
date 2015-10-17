#include "GameWindow.h"

GameWindow::GameWindow(const std::string& windowName, int width, int height)
	:width_(width), height_(height),
	window_(MySDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)),
	renderer_(MySDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)),
	camera_(width, height)
{
}

GameWindow::~GameWindow()
{
}

SDL_Window* GameWindow::getWindow()
{
	return window_.get();
}

SDL_Renderer* GameWindow::getRenderer()
{
	return renderer_.get();
}

Camera& GameWindow::getCamera()
{
	return camera_;
}

int GameWindow::getWidth() const
{
	return width_;
}

int GameWindow::getHeight() const
{
	return height_;
}




