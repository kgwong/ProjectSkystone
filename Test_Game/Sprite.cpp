#include "Sprite.h"

#include "ResourceLocator.h"

Sprite::Sprite(GameWindow* window, std::shared_ptr<SDL_Texture> texture)
	:_window(window), _texture(texture)
{
	SDL_QueryTexture(_texture.get(), NULL, NULL, &_width, &_height);

	_drawDestination.w = _width;
	_drawDestination.h = _height;
}

Sprite::~Sprite()
{
}

int Sprite::getWidth() const
{
	return _width;
}

int Sprite::getHeight() const
{
	return _height;
}

void Sprite::setWidth(int w)
{
	_width = w;
	_drawDestination.w = w;
}

void Sprite::setHeight(int h)
{
	_height = h;
	_drawDestination.h = h;
}


void Sprite::render(int x, int y)
{
	Point cameraPos = _window->camera.getPos();
	_drawDestination.x = x - cameraPos.x;
	_drawDestination.y = y - cameraPos.y;
	SDL_RenderCopy(_window->renderer, _texture.get(), NULL, &_drawDestination);
}