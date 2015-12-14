#include "Tile.h"

#include "Level.h"
#include "GameConstants.h"
#include "RenderComponent.h"
#include "ColliderComponent.h"

Tile::Tile()
{
}

Tile::Tile(Point position)
	:GameObject(position)
{
}

Tile::Tile(int x, int y)
	:GameObject(x, y)
{
}

Tile::~Tile()
{
}

void Tile::update(Level& level)
{
	if (colliderComponent_)
		colliderComponent_->update(level);
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
	return EntityType::TILE;
}

void Tile::setColliderComponent(std::shared_ptr<ColliderComponent> colliderComponent)
{
	colliderComponent_ = colliderComponent;
	addComponent(colliderComponent_);
}
