#include "Tile.h"

Tile::Tile(GameWindow* window, 
			SDL_Texture* tileSetImage, 
			SDL_Rect tileRect, 
			TileType type, 
			int r, int c, int size)
	:_window(window), _tileSetImage(tileSetImage), _tileRect(tileRect), tileType(type)
{
	position.x = c * size;
	position.y = r * size;
	_drawDestination.w = size;
	_drawDestination.h = size;

	switch (tileType)
	{
	case EMPTY:
		_colliderComponent = nullptr;
		break;
	case SOLID:
		_colliderComponent = std::make_shared<ColliderComponent>(0, 0, size, size);
		break;
	case TRANSITION:
		_colliderComponent = std::make_shared<ColliderComponent>(size - 3, 0, 3, size);
		break;
	default:
		std::cout << "!!!!!" << std::endl;
	}
}


Tile::~Tile()
{
}

void Tile::update()
{
	if (_colliderComponent)
		_colliderComponent->update(*this);
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
	if (type == ComponentType::COLLIDER)
		return _colliderComponent.get();
	return nullptr;
}

EntityType Tile::getType() const
{
	return EntityType::ENVIRONMENT;
}
