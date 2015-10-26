#include "Tile.h"

#include "Level.h"
#include "GameConstants.h"

Tile::Tile(SpriteRenderer* renderer,
			TileType type, 
			int r, int c)
	:renderer_(renderer),
	_tileType(type)
{
	position.x = c * Constants::TILE_SIZE;
	position.y = r * Constants::TILE_SIZE;

	switch (_tileType)
	{
	case EMPTY:
		_colliderComponent = nullptr;
		break;
	case SOLID:
		_colliderComponent = std::make_shared<ColliderComponent>(0, 0, Constants::TILE_SIZE, Constants::TILE_SIZE);
		break;
	default:
		std::cout << "!!!!!" << std::endl;
	}

	addComponent(_colliderComponent.get());
	callStartOnComponents();
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
	renderer_->update(*this);
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
