#include "Tile.h"

#include "Level.h"
#include "GameConstants.h"

Tile::Tile(SpriteRenderer* renderer,
			TileType type, 
			int r, int c)
	:GameObject(c * Constants::TILE_SIZE, r * Constants::TILE_SIZE),
	renderComponent_(renderer),
	_tileType(type)
{
	/*
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

	addComponent(_colliderComponent.get());*/
//	callStartOnComponents();
}


Tile::~Tile()
{
}

void Tile::update(Level& level)
{
	if (colliderComponent_)
		colliderComponent_->update(*this, level);
}

void Tile::render(Level& level)
{
	renderComponent_->update(*this, level);
}	

void Tile::onCollision(CollisionInfo& collision)
{
}

TileType Tile::getTileType()
{
	return _tileType;
}

void Tile::setTileType(int tileType)
{
	_tileType = (TileType)tileType;
}

EntityType Tile::getType() const
{
	return EntityType::ENVIRONMENT;
}

void Tile::setRenderComponent(std::shared_ptr<RenderComponent> renderComponent)
{
	renderComponent_ = renderComponent;
	addComponent(renderComponent_.get());
}

void Tile::setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent)
{
	colliderComponent_ = colliderComponent;
	addComponent(colliderComponent_.get());
}
