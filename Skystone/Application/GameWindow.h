#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#include <SDL/SDL.h>

#include <string>
#include <memory>

#include "Camera.h"
#include "Errors.h"

struct SDL_WindowDestroyer
{
	void operator()(SDL_Window* window)
	{
		SDL_DestroyWindow(window);
	}
};

struct SDL_RendererDestroyer
{
	void operator()(SDL_Renderer* renderer)
	{
		SDL_DestroyRenderer(renderer);
	}
};

class GameWindow
{
public:
	GameWindow(const std::string& windowName, int width, int height);
	~GameWindow();

	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	Camera& getCamera();

	int getWidth() const;
	int getHeight() const;

	void render(SDL_Texture* texture, const SDL_Rect* srcrect, SDL_Rect* dstrect, const double angle,
		const SDL_Point* center, const SDL_RendererFlip flip);

	void render(SDL_Texture* texture, const SDL_Rect* srcrect, SDL_Rect* dstrect);
	void renderOnCamera(SDL_Texture* texture, const SDL_Rect* srcrect, const SDL_Rect* dstrect);

private:
	std::unique_ptr<SDL_Window, SDL_WindowDestroyer> window_;
	std::unique_ptr<SDL_Renderer, SDL_RendererDestroyer> renderer_;
	Camera camera_;
	int width_;
	int height_;

};

#endif //GAME_WINDOW_H

