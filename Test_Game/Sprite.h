#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include <SDL/SDL_image.h>

#include "GameWindow.h"
#include "Resources.h"
#include "Point.h"

class Sprite
{
public:
	Sprite(GameWindow* window, const std::string& filepath);
	~Sprite();

	void setWidth(int w);
	void setHeight(int h);
	void render(int x, int y);

	int getWidth() const;
	int getHeight() const;

private:
	GameWindow* _window;

	SDL_Texture* _image;
	SDL_Rect _drawDestination;

	int _width;
	int _height;
};


#endif //SPRITE_H