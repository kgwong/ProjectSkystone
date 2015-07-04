#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <string>

#include "Camera.h"
#include "Errors.h"

class GameWindow
{
public:
	GameWindow(std::string windowName, int width, int height);
	~GameWindow();

	int getWidth() const;
	int getHeight() const;


public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	Camera camera;

private:
	int _width;
	int _height;

};

#endif //GAMEWINDOW_H

