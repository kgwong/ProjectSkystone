#include "Tile.h"

Tile::Tile()
{
}

Tile::Tile(GameWindow* window, 
			SDL_Texture* tileSetImage, 
			SDL_Rect tileRect, 
			int tileType, 
			int r, int c, int size)
	:_window(window), _tileSetImage(tileSetImage), _tileRect(tileRect), tileType(tileType)
{
	position.x = c * size;
	position.y = r * size;
	width = size;
	height = size;
	_drawDestination.w = size;
	_drawDestination.h = size;
}


Tile::~Tile()
{
}

void Tile::update()
{
	_colliderComponent.update(*this);
}

void Tile::render()
{
	Point cameraPos = _window->camera.getPos();
	_drawDestination.x = position.x - cameraPos.x;
	_drawDestination.y = position.y - cameraPos.y;
	SDL_RenderCopy(_window->renderer, _tileSetImage, &_tileRect, &_drawDestination);
}	

Component* Tile::getComponent(ComponentType type)
{
	if (type == COLLIDER)
		return &_colliderComponent;
	return nullptr;
}

EntityType Tile::getType() const
{
	return ENVIRONMENT;
}
