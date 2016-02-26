#include "GameWindow.h"

#include "Resources\Resources.h"

#include "Log.h"
#include "Components/Render/TextRenderer.h"
GameWindow::GameWindow(const std::string& windowName, int width, int height)
	:width_(width), height_(height),
	window_(MySDL_CreateWindow(windowName.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN)),
	renderer_(MySDL_CreateRenderer(window_.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)),
	camera_(width, height)
{
	//move this out side 
	Resources::textureLoader.initGameWindow(this); 
	//sets default color of background. Useful for testing holes in graphics
	//default is black
	//SDL_SetRenderDrawColor(renderer_.get(), 255, 0, 0, 255);
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

void GameWindow::render(SDL_Texture* texture, const SDL_Rect* srcrect, SDL_Rect* dstrect, const double angle, const SDL_Point* center, const SDL_RendererFlip flip)
{
	dstrect->x = dstrect->x - camera_.getPosX();
	dstrect->y = dstrect->y - camera_.getPosY();
	SDL_RenderCopyEx(getRenderer(), texture, srcrect, dstrect, angle, center, flip);
}

void GameWindow::render(SDL_Texture* texture, const SDL_Rect* srcrect, SDL_Rect* dstrect)
{
	dstrect->x = dstrect->x - camera_.getPosX();
	dstrect->y = dstrect->y - camera_.getPosY();
	MySDL_RenderCopy(getRenderer(), texture, srcrect, dstrect);

}

void GameWindow::renderOnCamera(SDL_Texture * texture, const SDL_Rect * srcrect, const SDL_Rect * dstrect)
{
	MySDL_RenderCopy(getRenderer(), texture, srcrect, dstrect);
}

