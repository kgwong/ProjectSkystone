#include "Tile.h"

#include "Level.h"
#include "GameConstants.h"

Tile::Tile(GameWindow* window, 
			SDL_Texture* tileSetImage, 
			SDL_Rect tileRect, 
			TileType type, 
			int r, int c)
	:_window(window), _tileSetImage(tileSetImage), _tileRect(tileRect), _tileType(type)
{
	position.x = c * Constants::TILE_SIZE;
	position.y = r * Constants::TILE_SIZE;
	_drawDestination.w = Constants::TILE_SIZE;
	_drawDestination.h = Constants::TILE_SIZE;

	switch (_tileType)
	{
	case EMPTY:
		_colliderComponent = nullptr;
		break;
	case SOLID:
		_colliderComponent = std::make_shared<ColliderComponent>(0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE);
		break;
	case TRANSITION:
		//_colliderComponent = std::make_shared<ColliderComponent>(size - 3, 0, 3, size);
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

void Tile::onCollision(CollisionInfo& collision)
{
}

TileType Tile::getTileType()
{
	return _tileType;
}

EntityType Tile::getType() const
{
	return EntityType::ENVIRONMENT;
}
