#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <memory>

#include <SDL/SDL_image.h>

#include "GameWindow.h"
#include "Point.h"

class Sprite
{
public:
	Sprite(GameWindow* window, std::shared_ptr<SDL_Texture> texture);
	~Sprite();

	void setWidth(int w);
	void setHeight(int h);

	void render(int x, int y);
	void render(Point position);

	int getWidth() const;
	int getHeight() const;

private:
	GameWindow* _window;

	std::shared_ptr<SDL_Texture> _texture;
	SDL_Rect _drawDestination;

	int _width;
	int _height;
};


#endif //SPRITE_H